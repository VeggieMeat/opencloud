<?php

/**
 * @file
 * Custom views plugin query
 */

class opencloud_server_views_plugin_query extends views_plugin_query {

  function init($base_table = 'opencloud_server', $base_field = 'id', $options) {
    parent::init($base_table, $base_field, $options);
    $this->base_table = $base_table;
    $this->base_field = $base_field;

    $this->table_queue[$base_table] = array(
      'alias' => $base_table,
      'table' => $base_table,
      'relationship' => $base_table,
    );
    // init the tables with our primary table
    $this->tables[$base_table][$base_table] = array(
      'count' => 1,
      'alias' => $base_table,
    );

    $this->count_field = array(
      'table' => $base_table,
      'field' => $base_field,
      'alias' => $base_field,
      'count' => TRUE,
    );
  }

  function add_field($table = 'opencloud_server', $field, $alias = '', $params = array()) {
    // We check for this specifically because it gets a special alias.
    if ($table == $this->base_table && $field == $this->base_field && empty($alias)) {
      $alias = $this->base_field;
    }

    if ($table && empty($this->table_queue[$table])) {
      $this->ensure_table($table);
    }

    if (!$alias && $table) {
      $alias = $table . '_' . $field;
    }

    // Make sure an alias is assigned
    $alias = $alias ? $alias : $field;

    // Create field info array.
    $field_info = array(
      'field' => $field,
      'table' => $table,
      'alias' => $alias,
    ) + $params;

    if (empty($this->fields[$alias])) {
      $this->fields[$alias] = $field_info;
    }

    return $alias;
  }

  function add_relationship($alias, $join, $base, $link_point = NULL) {
    if (empty($link_point)) {
      $link_point = $this->base_table;
    }
    elseif (!array_key_exists($link_point, $this->relationships)) {
      return FALSE;
    }

    // Make sure $alias isn't already used; if it, start adding stuff.
    $alias_base = $alias;
    $count = 1;
    while (!empty($this->relationships[$alias])) {
      $alias = $alias_base . '_' . $count++;
    }

    // Make sure this join is adjusted for our relationship.
    if ($link_point && isset($this->relationships[$link_point])) {
      $join = $this->adjust_join($join, $link_point);
    }

    // Add the table directly to the queue to avoid accidentally marking
    // it.
    $this->table_queue[$alias] = array(
      'table' => $join->table,
      'num' => 1,
      'alias' => $alias,
      'join' => $join,
      'relationship' => $link_point,
    );

    $this->relationships[$alias] = array(
      'link' => $link_point,
      'table' => $join->table,
      'base' => $base,
    );

    $this->tables[$this->base_table][$alias] = array(
      'count' => 1,
      'alias' => $alias,
    );

    return $alias;
  }

  function add_table($table, $relationship = NULL, $join = NULL, $alias = NULL) {
    if (!$this->ensure_path($table, $relationship, $join)) {
      return FALSE;
    }

    if ($join && $relationship) {
      $join = $this->adjust_join($join, $relationship);
    }

    return $this->queue_table($table, $relationship, $join, $alias);
  }

  function add_tag($tag) {
    $this->tags[] = $tag;
  }

  function add_where($group, $field, $value = NULL, $operator = NULL) {
    if ('opencloud_server.tenant_id' == $field) {
      $this->provider = opencloud_provider_load_by_tenant_id($value);
    }
  }

  function adjust_join($join, $relationship) {
    if (!empty($join->adjusted)) {
      return $join;
    }

    if (empty($relationship) || empty($this->relationships[$relationship])) {
      return $join;
    }

    // Adjusts the left table for our relationship.
    if ($relationship != $this->base_table) {
      // If we're linking to the primary table, the relationship to use will
      // be the prior relationship. Unless it's a direct link.

      // Safety! Don't modify an original here.
      $join = clone $join;

      // Do we need to try to ensure a path?
      if ($join->left_table != $this->relationships[$relationship]['table'] && $join->left_table != $this->relationships[$relationship]['base'] && !isset($this->tables[$relationship][$join->left_table]['alias'])) {
        $this->ensure_table($join->left_table, $relationship);
      }

      // First, if this is our link point/anchor table, just use the relationship
      if ($join->left_table == $this->relationships[$relationship]['table']) {
        $join->left_table = $relationship;
      }
      // then, try the base alias.
      elseif (isset($this->tables[$relationship][$join->left_table]['alias'])) {
        $join->left_table = $this->tables[$relationship][$join->left_table]['alias'];
      }
      // But if we're already looking at an alias, use that instead.
      elseif (isset($this->table_queue[$relationship]['alias'])) {
        $join->left_table = $this->table_queue[$relationship]['alias'];
      }
    }

    $join->adjusted = TRUE;
    return $join;
  }

  function ensure_table($table, $relationship = NULL, $join = NULL) {
    // ensure a relationship
    if (empty($relationship)) {
      $relationship = $this->base_table;
    }

    // If the relationship is the primary table, this actually be a relationship
    // link back from an alias. We store all aliases along with the primary table
    // to detect this state, because eventually it'll hit a table we already
    // have and that's when we want to stop.
    if ($relationship == $this->base_table && !empty($this->tables[$relationship][$table])) {
      return $this->tables[$relationship][$table]['alias'];
    }

    if (!array_key_exists($relationship, $this->relationships)) {
      return FALSE;
    }

    if ($table == $this->relationships[$relationship]['base']) {
      return $relationship;
    }

    // If we do not have join info, fetch it.
    if (!isset($join)) {
      $join = $this->get_join_data($table, $this->relationships[$relationship]['base']);
    }

    // If it can't be fetched, this won't work.
    if (empty($join)) {
      return;
    }

    // Adjust this join for the relationship, which will ensure that the 'base'
    // table it links to is correct. Tables adjoined to a relationship
    // join to a link point, not the base table.
    $join = $this->adjust_join($join, $relationship);

    if ($this->ensure_path($table, $relationship, $join)) {
      // Attempt to eliminate redundant joins.  If this table's
      // relationship and join exactly matches an existing table's
      // relationship and join, we do not have to join to it again;
      // just return the existing table's alias.  See
      // http://groups.drupal.org/node/11288 for details.
      //
      // This can be done safely here but not lower down in
      // queue_table(), because queue_table() is also used by
      // add_table() which requires the ability to intentionally add
      // the same table with the same join multiple times.  For
      // example, a view that filters on 3 taxonomy terms using AND
      // needs to join taxonomy_term_data 3 times with the same join.

      // scan through the table queue to see if a matching join and
      // relationship exists.  If so, use it instead of this join.

      // TODO: Scanning through $this->table_queue results in an
      // O(N^2) algorithm, and this code runs every time the view is
      // instantiated (Views 2 does not currently cache queries).
      // There are a couple possible "improvements" but we should do
      // some performance testing before picking one.
      foreach ($this->table_queue as $queued_table) {
        // In PHP 4 and 5, the == operation returns TRUE for two objects
        // if they are instances of the same class and have the same
        // attributes and values.
        if ($queued_table['relationship'] == $relationship && $queued_table['join'] == $join) {
          return $queued_table['alias'];
        }
      }

      return $this->queue_table($table, $relationship, $join);
    }
  }

  function execute(&$view) {
    if ($this->provider) {
      $this->cloud = opencloud_provider_connect($this->provider);
      $this->compute = $this->cloud->Compute(NULL, $this->provider->region);
      $this->servers = $this->compute->ServerList();
      while ($server = $this->servers->Next()) {
        $view->result[] = (object) $server;
      }
    }
  }
}

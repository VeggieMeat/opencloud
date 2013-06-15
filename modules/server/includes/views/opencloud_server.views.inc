<?php

/**
 * @file
 * Views hooks for Opencloud Server.
 */

/**
 * Implements hook_views_data().
 */
function opencloud_server_views_data() {
  $data = array();
  $data['opencloud_server']['table']['group'] = t('Opencloud Server');

  $data['opencloud_server']['table']['base'] = array(
    'title' => t('Opencloud Server'),
    'help' => t('Queries an Openstack-based server.'),
    'query class' => 'opencloud_server',
  );
}

/**
 * Implements hook_views_plugins().
 */
function opencloud_server_views_plugins() {
  return array(
    'query' => array(
      'opencloud_server' => array(
        'title' => t('Opencloud Server Query'),
        'help' => t('Query will be generated and run against an Openstack-based Compute endpoint.'),
        'handler' => 'opencloud_server_plugin_query',
      ),
    ),
  );
}

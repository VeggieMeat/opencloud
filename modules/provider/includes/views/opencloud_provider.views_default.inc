<?php

/**
 * @file
 * Views for the default Provider UI.
 */

/**
 * Implements hook_views_default_views().
 */
function opencloud_provider_ui_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'oc_providers';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'opencloud_provider';
  $view->human_name = 'Providers';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Providers';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer opencloud_providerentities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'provider_id' => 'provider_id',
    'name' => 'name',
    'password' => 'password',
    'region' => 'region',
    'type' => 'type',
    'url' => 'url',
    'username' => 'username',
    'tenant_id' => 'tenant_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'provider_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'password' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'region' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'url' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'username' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tenant_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      ),
  );
  /* Field: Opencloud Provider: Provider Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'opencloud_provider';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Name';
  /* Field: Opencloud Provider: Provider Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'opencloud_provider';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = 'Type';
  /* Field: Opencloud Provider: Provider Region */
  $handler->display->display_options['fields']['region']['id'] = 'region';
  $handler->display->display_options['fields']['region']['table'] = 'opencloud_provider';
  $handler->display->display_options['fields']['region']['field'] = 'region';
  $handler->display->display_options['fields']['region']['label'] = 'Region';
  /* Field: Opencloud Provider: Tenant ID */
  $handler->display->display_options['fields']['tenant_id']['id'] = 'tenant_id';
  $handler->display->display_options['fields']['tenant_id']['table'] = 'opencloud_provider';
  $handler->display->display_options['fields']['tenant_id']['field'] = 'tenant_id';
  /* Field: Opencloud Provider: Provider Username */
  $handler->display->display_options['fields']['username']['id'] = 'username';
  $handler->display->display_options['fields']['username']['table'] = 'opencloud_provider';
  $handler->display->display_options['fields']['username']['field'] = 'username';
  $handler->display->display_options['fields']['username']['label'] = 'Username';
  /* Field: Opencloud Provider: Provider Password */
  $handler->display->display_options['fields']['password']['id'] = 'password';
  $handler->display->display_options['fields']['password']['table'] = 'opencloud_provider';
  $handler->display->display_options['fields']['password']['field'] = 'password';
  $handler->display->display_options['fields']['password']['label'] = 'Password';
  /* Field: Opencloud Provider: Provider URL */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'opencloud_provider';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['label'] = 'Auth URL';

  /* Display: Admin page */
  $handler = $view->new_display('page', 'Admin page', 'admin_page');
  $handler->display->display_options['path'] = 'admin/opencloud/providers/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Providers';
  $handler->display->display_options['tab_options']['description'] = 'Manage your available service providers';
  $handler->display->display_options['tab_options']['weight'] = '0';

  $views[$view->name] = $view;

  return $views;
}

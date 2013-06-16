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

  $data['opencloud_server']['id'] = array(
    'title' => t('Remote ID'),
    'help' => t('The remote ID of the server.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['hostId'] = array(
    'title' => t('Host'),
    'help' => t('The host node where the server resides.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['uuid'] = array(
    'title' => t('UUID'),
    'help' => t('The remote UUID of the server (not used by all providers).'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['user_id'] = array(
    'title' => t('User ID'),
    'help' => t('The remote User ID of the server.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['tenant_id'] = array(
    'title' => t('Tenant ID'),
    'help' => t('The remote Tenant ID of the server.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['name'] = array(
    'title' => t('Name'),
    'help' => t('The name of the server.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['status'] = array(
    'title' => t('Status'),
    'help' => t('The status of the server.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['progress'] = array(
    'title' => t('Progress'),
    'help' => t('The progress of the server in the current state.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['accessIPv4'] = array(
    'title' => t('IPv4'),
    'help' => t('The publicly accessible IPv4 address (not used by some providers).'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['accessIPv6'] = array(
    'title' => t('IPv6'),
    'help' => t('The publicly accessible IPv6 address (not used by some providers).'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['created'] = array(
    'title' => t('Created'),
    'help' => t('The date and time when the server was created.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['updated'] = array(
    'title' => t('Updated'),
    'help' => t('The date and time when the server was most recently updated.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );
  return $data;
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
        'handler' => 'opencloud_server_views_plugin_query',
      ),
    ),
  );
}

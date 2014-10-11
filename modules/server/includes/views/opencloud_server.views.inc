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
//    'query class' => 'opencloud_server',
  );

  $data['opencloud_server']['server_id'] = array(
    'title' => t('Server ID'),
    'help' => t('The ID of the server.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['provider_id'] = array(
    'title' => t('Provider ID'),
    'help' => t('The ID of the Provider for the server.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['name'] = array(
    'title' => t('Name'),
    'help' => t('The name of the server'),
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

  $data['opencloud_server']['hostid'] = array(
    'title' => t('Host'),
    'help' => t('The host node where the server resides.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['uuid'] = array(
    'title' => t('UUID'),
    'help' => t('The UUID of the server (not used by all providers).'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['image'] = array(
    'title' => t('Image'),
    'help' => t('The image used to build the server.'),
    'field' => array(
      'handler' => 'opencloud_server_views_handler_field',
    ),
  );

  $data['opencloud_server']['flavor'] = array(
    'title' => t('Flavor'),
    'help' => t('The flavor of the server.'),
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

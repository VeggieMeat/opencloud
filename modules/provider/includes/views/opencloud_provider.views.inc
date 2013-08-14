<?php

/**
 * @file
 * Expose Opencloud provider data to Views
 */

/**
 * Implements hook_views_data().
 */
function opencloud_provider_views_data() {
  $data = array();

  $data['opencloud_provider']['table']['group']  = t('Opencloud Provider');

  $data['opencloud_provider']['table']['base'] = array(
    'field' => 'provider_id',
    'title' => t('Opencloud Provider'),
    'help' => t('Opencloud providers.'),
    'access query tag' => 'opencloud_provider_access',
  );
  $data['opencloud_provider']['table']['entity type'] = 'opencloud_provider';

  // Expose the Provider ID.
  $data['opencloud_provider']['provider_id'] = array(
    'title' => t('Provider ID'),
    'help' => t('The unique internal identifier of the provider.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the Provider Name.
  $data['opencloud_provider']['name'] = array(
    'title' => t('Provider Name'),
    'help' => t('The name of the provider.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the Provider Type.
  $data['opencloud_provider']['type'] = array(
    'title' => t('Provider Type'),
    'help' => t('The type of the provider.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the Provider authentication URL.
  $data['opencloud_provider']['url'] = array(
    'title' => t('Provider URL'),
    'help' => t('The authentication URL of the provider.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Expose the Provider Username.
  $data['opencloud_provider']['username'] = array(
    'title' => t('Provider Username'),
    'help' => t('The username used with this provider.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Expose the Provider Password or API Key.
  $data['opencloud_provider']['password'] = array(
    'title' => t('Provider Password'),
    'help' => t('The password, API key, or other authentication token used with this provider.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['opencloud_provider']['tenant_id'] = array(
    'title' => t('Tenant ID'),
    'help' => t('The tenant ID used with this provider.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Expose the Provider Region.
  $data['opencloud_provider']['region'] = array(
    'title' => t('Provider Region'),
    'help' => t('The region the credentials apply to for this provider.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

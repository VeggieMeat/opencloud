<?php

/**
 * @file
 * Contains admin forms, handlers and functions for Opencloud Provider UI.
 */

/**
 * Settings form.
 */
function opencloud_provider_ui_settings() {
  $form = array();

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Provider Name'),
    '#description' => t('The name of this Provider.'),
    '#required' => TRUE,
  );

  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Authentication URL'),
    '#description' => t('The endpoint URL for authentication'),
    '#required' => TRUE,
  );

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t('This chooses which class in the API to use with this Provider. If your provider is not listed by name, then choose OpenStack.'),
    '#options' => opencloud_provider_ui_get_type_options(),
    '#required' => TRUE,
  );

  $form['region'] = array(
    '#type' => 'textfield',
    '#title' => t('Region'),
    '#description' => t('The region for this Provider.'),
    '#required' => TRUE,
  );

  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('The username used for this Provider.'),
    '#required' => TRUE,
  );

  $form['password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#description' => t('The password, API key, or other authentication token for this Provider.'),
    '#required' => TRUE,
  );

  $form['tenant_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Tenant ID'),
    '#description' => t('The tenant ID for this Provider.'),
    '#required' => TRUE,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save provider'),
    '#submit' => array('opencloud_provider_ui_provider_form_submit'),
  );

  return $form;
}

/**
 * Submit handler for Provider form.
 */
function opencloud_provider_ui_provider_form_submit($form, &$form_state) {
  global $user;

  $provider = entity_get_controller('opencloud_provider')->create();

  foreach ($form_state['values'] as $field => $value) {
    $provider->$field = $value;
  }

  if (empty($provider->uid)) {
    $provider->uid = $user->uid;
  }

  $provider->created = REQUEST_TIME;
  $provider->updated = REQUEST_TIME;

  opencloud_provider_save($provider);

  if ($provider->provider_id) {
    drupal_set_message(t('Provider %name has been saved.', array('%name' => $provider->name)));
    $form_state['redirect'] = 'admin/opencloud/providers';
  }
}

/**
 * Get an array of options for type settings.
 */
function opencloud_provider_ui_get_type_options() {
  $options = array();

  $types = opencloud_provider_types();
  foreach ($types as $class => $description) {
    $options[$class] = $class;
  }

  return $options;
}

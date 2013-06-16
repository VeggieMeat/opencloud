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

  return system_settings_form($form);
}

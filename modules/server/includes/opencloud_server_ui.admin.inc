<?php

/**
 * @file
 * Contains administration forms for Opencloud Server
 */

/**
 * Universal settings form.
 */
function opencloud_server_ui_settings() {
  $form = array();
  $form['opencloud_server_expiration'] = array(
    '#type' => 'textfield',
    '#title' => t('Time to wait before automatically checking a remote server for updated information.'),
    '#default_value' => variable_get('opencloud_server_expiration', 600),
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('Time is in seconds. Default is 600.'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Validate settings.
 */
function opencloud_server_ui_settings_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['opencloud_server_expiration'])) {
    form_set_error('opencloud_server_expiration', t('You must enter an integer for the expiration time.'));
  }
  elseif (0 >= $form_state['values']['opencloud_server_expiration']) {
    form_set_error('opencloud_server_expiration', t('Expiration time must be positive.'));
  }
}

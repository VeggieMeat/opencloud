<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Allows modules to alter Opencloud Provider credentials array.
 *
 * By default, credentials are passed using an array with a username and a
 * password. However, some providers would rather the "password" field be named
 * "apiKey" (such as Rackspace), and yet others may also need the Tenant ID.
 *
 * @param obj $provider
 *   The Provider entity object.
 *
 * @return array
 *   An array of keys and values to use for authentication.
 */
function hook_opencloud_provider_credentials($provider) {
  // To avoid conflicts with other modules, you should make sure to only return
  // a credentials array for the Provider that your module is for.
  if ('Rackspace' == $provider->type) {
    return array(
      'username' => $provider->username,
      'apiKey' => $provider->password,
    );
  }
}

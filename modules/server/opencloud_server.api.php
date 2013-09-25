<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Allows modules to alter Opencloud Server property mappings for their needs.
 *
 * The Opencloud Server module provides a set of default properties and
 * mappings common across most Openstack providers. However, some providers
 * implement their own properties for their deployments.
 *
 * Remember to define these properties with hook_entity_property_info_alter().
 *
 * @param array $properties
 *   A property mapping array.
 * @param array $context
 *   - server: A clone of the Openstack server object.
 *   - provider: A clone of the Opencloud provider entity.
 */
function hook_opencloud_server_map_properties_alter(&$properties, $context) {
  $server = $context['server'];
  $provider = $context['provider'];
  // To avoid conflicts with other modules, you should make sure to only alter
  // properties for the Provider that your module uses. Also, it would be very
  // much appreciated if you prefix these properties with something that is
  // unique for that provider, such as 'hp_' or 'rax_'.
  if ('Rackspace' == $provider->type) {
    $properties['rax_property'] = $server->property;
  }
}

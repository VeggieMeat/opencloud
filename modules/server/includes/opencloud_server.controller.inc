<?php

/**
 * Entity controller implementing EntityAPIControllerInterface
 *
 * Based on RemoteEntityAPIDefaultController.
 */
class OpencloudServerEntityController extends EntityAPIController implements EntityAPIControllerInterface {

  /**
   * Determines whether  to bypass remote retrieval of entities.
   */
  public $bypass_remote_retrieve = FALSE;

  /**
   * Overridden to retrieve entities from remote source if expired.
   *
   * Retrieving remote entities can be bypassed by setting the value of the
   * property $bypass_remote_retrieve on the controller object to TRUE.
   *
   * @see DrupalDefaultEntityController#load($ids,$conditions)
   */
  public function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);

    // Check for expiry, allowing the controller setting to bypass this.
    if (!$this->bypass_remote_retrieve) {
      foreach ($entities as $id => $entity) {
        // A value of 0 for the expiry means it doesn't expire.
        if (!empty($entity->expires) && $entity->expires < REQUEST_TIME) {
          // Entity has expired.
          // Fetch the remote server and update.
          $compute = opencloud_server_compute($entity->provider_id);
          $server = opencloud_server_fetch_server($compute, $entity->uuid);
          if (!empty($server)) {
            $entities[$id] = opencloud_server_map_properties($server, $entity);
          }
        }
      }
    }

    return $entities;
  }

  /**
   * Save the remote server.
   *
   * This simply overrides the default save function.
   *
   * @param obj $entity
   *   The entity to save.
   * @param array $remote_properties
   *   (Optional) An array of properties to save.
   */
  public function save($entity, $remote_properties = array()) {
    // Bypass remote retrievals.
    $this->bypass_remote_retrieve = TRUE;

    if (!$entity->uuid) {
      $compute = opencloud_server_compute($entity->provider_id);
      opencloud_server_create_server($server, $remote_properties);
    }
    else {
      try {
        $server = opencloud_server_fetch_server($compute, $entity->uuid);
        $server->update($remote_properties);
      }
      catch (\Guzzle\Http\Exception\BadResponseException $e) {
        if ('404' == $e->getResponse()->getStatusCode()) {
          $server = $compute->server();
          opencloud_server_create_server($server, $remote_properties);
        }
        else {
          watchdog('opencloud_server', print_r($e, TRUE), array(), WATCHDOG_WARNING);
        }
      }
    }

    $entity->expires = REQUEST_TIME + variable_get('opencloud_server_expiration', 600);
    $return = parent::save($entity);

    return $return;
  }
}

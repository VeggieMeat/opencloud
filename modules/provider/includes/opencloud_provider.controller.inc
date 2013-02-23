<?php

/**
 * @file
 * The controller for the provider entity containing the CRUD operations.
 */

/**
 * The controller class for providers contains methods for the provider CRUD
 * operations.
 */
class OpencloudProviderEntityController extends EntityAPIController {

  /**
   * Creates a default provider.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   *
   * @return object
   *   A provider object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'provider_id' => NULL,
      'is_new' => NULL,
      'name' => '',
      'tenant_id' => '',
      'username' => '',
      'password' => '',
      'token' => '',
      'created' => '',
      'changed' => '',
    );

    return parent::create($values);
  }

  /**
   * Saves a provider.
   *
   * @param $provider
   *   The full provider object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return int
   */
  public function save($provider, DatabaseTransaction $transaction = NULL) {
    global $user;

    $provider->changed = REQUEST_TIME;

    if (empty($provider->{$this->idKey}) || !empty($provider->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($provider->created)) {
        $provider->created = REQUEST_TIME;
      }
    }

    // Determine if we will be inserting a new provider.
    $provider->is_new = empty($provider->provider_id);

    return parent::save($provider, $transaction);
  }

  /**
   * Deletes multiple providers by ID.
   *
   * @param $provider_ids
   *   An array of provider IDs to delete.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($provider_ids, DatabaseTransaction $transaction = NULL) {
    if (!empty($provider_ids)) {
      $providers = $this->load($provider_ids, array());

      // Ensure the providers can actually be deleted.
      foreach ((array) $providers as $provider_id => $provider) {
        if (!opencloud_provider_can_delete($provider)) {
          unset($providers[$provider_id]);
        }
      }

      // If none of the specified providers can be deleted, return FALSE.
      if (empty($providers)) {
        return FALSE;
      }

      parent::delete(array_keys($providers), $transaction);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
}

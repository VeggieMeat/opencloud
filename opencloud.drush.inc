<?php

/**
 * @file
 *   drush integration for Opencloud.
 */

/**
 * The Opencloud plugin URI.
 */
define('OPENCLOUD_DOWNLOAD_URI', 'https://github.com/rackspace/php-opencloud/archive/v1.5.7.tar.gz');
define('OPENCLOUD_DOWNLOAD_PREFIX', 'php-opencloud-');

/**
 * Implementation of hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * See `drush topic docs-commands` for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function opencloud_drush_command() {
  $items = array();

  // the key in the $items array is the name of the command.
  $items['opencloud-sdk'] = array(
    'callback' => 'drush_opencloud_sdk',
    'description' => dt('Download and install the PHP-Opencloud SDK.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap.
    'arguments' => array(
      'path' => dt('Optional. A path where to install the PHP-Opencloud SDK. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('ocsdk'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function opencloud_drush_help($section) {
  switch ($section) {
    case 'drush:opencloud-sdk':
      return dt('Download and install the PHP-Opencloud SDK from github.com/rackspace/php-opencloud.git, default location is sites/all/libraries.');
  }
}

/**
 * Command to download the PHP-Opencloud SDK.
 */
function drush_opencloud_sdk() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = 'sites/all/libraries';
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  // Download the zip archive
  if ($filepath = drush_download_file(OPENCLOUD_DOWNLOAD_URI)) {
    $filename = basename($filepath);
    $dirname = OPENCLOUD_DOWNLOAD_PREFIX . basename($filepath, '.tar.gz');

     // Remove any existing Opencloud plugin directory
    if (is_dir($dirname) || is_dir('php-opencloud')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir('php-opencloud', TRUE);
      drush_log(dt('An existing PHP-Opencloud SDK was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive
    drush_tarball_extract($filename);

    // Change the directory name to "opencloud" if needed.
    if ($dirname != 'php-opencloud') {
      drush_move_dir($dirname, 'php-opencloud', TRUE);
      $dirname = 'php-opencloud';
    }
  }

  if (is_dir($dirname)) {
    drush_log(dt('PHP-Opencloud SDK has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the PHP-Opencloud SDK to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}

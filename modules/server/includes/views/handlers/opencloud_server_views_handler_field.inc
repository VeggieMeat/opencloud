<?php

class opencloud_server_views_handler_field extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);

    if (!empty($this->options['link_to_server'])) {
      $this->additional_fields['server_id'] = 'server_id';
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['link_to_server'] = array('default' => FALSE);

    return $options;
  }

  /**
   * Provide the link to server option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_to_server'] = array(
      '#title' => t("Link this field to the server's administrative view page"),
      '#description' => t('This will override any other link you have set.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_server']),
    );
  }

  /**
   * Render whatever the data is as a link to the server.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_server']) && $data !== NULL && $data !== '') {
      $server_id = $this->get_value($values, 'server_id');
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = 'admin/opencloud/servers/' . $server_id;
    }

    return $data;
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }
}

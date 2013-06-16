<?php

class opencloud_server_views_handler_field extends views_handler_field {

  function query() {
    $this->add_additional_fields();
  }

  function render($values) {
    $field_name = $this->real_field;
    return check_plain($values->$field_name);
  }

}

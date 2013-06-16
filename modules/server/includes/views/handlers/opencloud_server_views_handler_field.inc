<?php

class opencloud_server_views_handler_field extends views_handler_field {

  function query() {
    $this->add_additional_fields();
  }

  function render($values) {
    if (isset($values->{$this->real_field})) {
      return check_plain($values->{$this->real_field});
    }
  }

}

<?php

use Drupal\Core\Render\Element\StatusMessages;

/**
 * Implements hook_preprocess_block_HOOK() for HTML document templates.
 */
function skenografia_preprocess_block__system_messages_block(&$variables) {
  // 10.3 upgrade now missing status-message theme suggestions https://www.drupal.org/project/drupal/issues/3456176
  $variables['content'] = StatusMessages::renderMessages();
}

<?php

/**
 * @file
 * Hook THEME_suggestions_*.
 */

use Drupal\bootstrap_italia\Helper\Suggestions;

/**
 * Implements hook_theme_suggestions_page_alter().
 */
function skenografia_theme_suggestions_page_alter(array &$suggestions, array &$variables): void {
  $current_path = \Drupal::service('path.current')->getPath();
  $path = Suggestions::sanitize(Drupal::service('path_alias.manager')->getAliasByPath($current_path));
  $suggestions[] = $variables['theme_hook_original'] . '__path' . str_replace('/', '__', $path);
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function skenografia_theme_suggestions_node_alter(array &$suggestions, array $variables): void {
  if (in_array('node__type_page__view_mode_full', $suggestions, TRUE)) {
    $current_path = \Drupal::service('path.current')->getPath();
    $path = Suggestions::sanitize(Drupal::service('path_alias.manager')->getAliasByPath($current_path));
    $suggestions[] = 'node__type_page__view_mode_full' . '__path' . str_replace('/', '__', $path);
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function skenografia_theme_suggestions_views_view_fields_alter(array &$suggestions, array &$variables): void {
  if (isset($variables['view'])) {
    $view = $variables['view'];
    $displayObj = $view->getDisplay();
    $suggestions[] = $variables['theme_hook_original'] . '__' . $view->id();
    $suggestions[] = $variables['theme_hook_original'] . '__' . $view->id() . '__' . $displayObj->display['id'];
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function skenografia_theme_suggestions_views_view_field_alter(array &$suggestions, array &$variables): void {
  if (isset($variables['field']) && isset($variables['view'])) {
    $field = $variables['field'];
    $view = $variables['view'];
    $displayObj = $view->getDisplay();
    $suggestions[] = $variables['theme_hook_original'] . '__' . $field->field;
    $suggestions[] = $variables['theme_hook_original'] . '__' . $view->id() . '__' . $field->field;
    $suggestions[] = $variables['theme_hook_original'] . '__' . $view->id() . '__' . $displayObj->display['id'] . '__' . $field->field;
  }
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function skenografia_theme_suggestions_views_view_grouping_alter(array &$suggestions, array &$variables):void {
  if (isset($variables['grouping']) && isset($variables['view'])) {
    $view = $variables['view'];
    $displayObj = $view->getDisplay();
    $suggestions[] = $variables['theme_hook_original'] . '__' . $variables['grouping']['field'];
    $suggestions[] = $variables['theme_hook_original'] . '__' . $view->id() . '__' . $variables['grouping']['field'];
    $suggestions[] = $variables['theme_hook_original'] . '__' . $view->id() . '__' . $displayObj->display['id'] . '__' . $variables['grouping']['field'];
  }
}

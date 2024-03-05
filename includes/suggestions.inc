<?php

/**
 * @file
 * Hook THEME_suggestions_*.
 */

function skenografia_theme_suggestions_views_view_fields_alter(array &$suggestions, array &$variables): void {
  if (isset($variables['view'])) {
    $view = $variables['view'];
    $displayObj = $view->getDisplay();
    $suggestions[] = $variables['theme_hook_original'] . '__' . $view->id();
    $suggestions[] = $variables['theme_hook_original'] . '__' . $view->id() . '__' . $displayObj->display['id'];
  }
}

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

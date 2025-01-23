<?php

/**
 * @file
 * Hook THEME_suggestions_*.
 */

use Drupal\bootstrap_italia\Helper\Suggestions;
use Drupal\taxonomy\Entity\Term;

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

function skenografia_theme_suggestions_views_view_table_alter(array &$suggestions, array &$variables): void {
  $term = \Drupal::routeMatch()->getParameter('taxonomy_term');
  if ($term instanceof Term) {
    $suggestions[] = $variables['theme_hook_original'] . '__term';
    $suggestions[] = $variables['theme_hook_original'] . '__term__bundle_' . Suggestions::sanitize($term->bundle());
    $suggestions[] = $variables['theme_hook_original'] . '__term__id_' . Suggestions::sanitize($term->id());
  }
}

/**
 * Implements hook_theme_suggestions_taxonomy_term_alter().
 *
 * Ref: https://www.drupal.org/project/coding_standards/issues/3056368
 *
 * @phpstan-ignore missingType.iterableValue, missingType.iterableValue
 */
function skenografia_theme_suggestions_taxonomy_term_alter(array &$suggestions, array $variables): void {
  if (
    isset($variables['elements']['#view_mode']) &&
    isset($variables['elements']['#taxonomy_term']) &&
    ($variables['elements']['#taxonomy_term'] instanceof Term)
  ) {
    $suggestions[] = $variables['theme_hook_original']
      . '__type_' . $variables['elements']['#taxonomy_term']->bundle()
      . '__view_mode_' . $variables['elements']['#view_mode']
      . '__tid_' . $variables['elements']['#taxonomy_term']->get('tid')->value;
  }
}

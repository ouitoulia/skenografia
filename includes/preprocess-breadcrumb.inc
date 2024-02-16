<?php

/**
 * @file
 * Preprocess breadcrumb.
 */

use Drupal\Core\Template\Attribute;

/**
 * Implements hook_preprocess_HOOK() for breadcrumb.html.twig.
 */
function skenografia_preprocess_breadcrumb(array &$variables): void {
  $route_match = Drupal::routeMatch();

  // Add current page to breadcrumb.
  if ($route_match->getRouteName() == 'entity.node.canonical' && $variables['breadcrumb']) {

    $request = Drupal::request();
    $node = $request->attributes->get('node');

    if ($node->getType() == 'classe') {
      $page_title = Drupal::service('title_resolver')->getTitle($request, $route_match->getRouteObject());
      $page_title_sanitized = trim(explode("#", $page_title)[0]);

      // Fix cache.
      $variables['#cache']['contexts'][] = 'url';
      $variables['breadcrumb'][ array_key_last($variables['breadcrumb']) ]["text"] = $page_title_sanitized;
    }
  }
}

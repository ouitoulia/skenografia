<?php

namespace Drupal\skenografia\Helper;

use Drupal\Core\Config\Config;
use Drupal\Core\Theme\ActiveTheme;

/**
 * Helper class for Skenografia theme.
 *
 * Why isn't it a service? https://www.drupal.org/project/drupal/issues/2002606.
 */
class Helper {

  /**
   * Return a comune and provincia from luogo.field_indirizzo.
   *
   * @return array
   *   Comune and provincia.
   * @throws \Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException
   * @throws \Drupal\Component\Plugin\Exception\PluginNotFoundException
   */
  public static function getLocality(): array {
    $data = [];

    // https://www.drupal.org/docs/drupal-apis/entity-api/working-with-the-entity-api#s-query-the-database-for-entities-matching-some-conditions
    $nodeStorage = \Drupal::entityTypeManager()->getStorage('node');
    $ids = $nodeStorage->getQuery()
      ->accessCheck(TRUE)
      ->condition('type','luogo')
      ->condition('status', 1)
      ->condition('field_sede_legale', 1)
      ->execute();
    $nodes = $nodeStorage->loadMultiple($ids);

    if (count($nodes) === 1) {
      /** @var Drupal\node\Entity\Node $sede_legale */
      $sede_legale = $nodes[array_key_first($nodes)];
      if ($sede_legale->hasField('field_indirizzo')) {
        $indirizzo = $sede_legale->get('field_indirizzo')->first();
        if (!empty($indirizzo)) {
          $locality = $indirizzo->get('locality')->getValue();
          if (!empty($locality)) {
            $data['comune'] = $locality;
          }
          $administrative_area = $indirizzo->get('administrative_area')->getValue();
          if (!empty($administrative_area)) {
            $data['provincia'] = $administrative_area;
          }
        }
      }
    }

    return $data;
  }

}

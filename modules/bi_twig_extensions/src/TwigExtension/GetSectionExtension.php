<?php

namespace Drupal\bi_twig_extensions\TwigExtension;

use Twig\Extension\AbstractExtension;
use Twig\TwigFunction;

/**
 * GetSectionExtension provides function and filter.
 */
class GetSectionExtension extends AbstractExtension {

  /**
   * Declare your custom twig function here.
   *
   * @return \Twig\TwigFunction[]
   *   TwigFunction array.
   */
  public function getFunctions() {
    return [
      new TwigFunction('get_section_by_bundle',
        [$this, 'getSectionByBundle'],
        ['is_safe' => ['html']]
      ),
    ];
  }

  /**
   * Provides school section name for bundle.
   *
   * @param string $block_id
   *   Valid block id.
   *
   * @return array|string
   *   NUll or render array of block.
   */
  public function getSectionByBundle(string $bundle) {

    if ($bundle) {
      $bundles = [
        [
          'name' => 'scuola',
          'value'=> [
            'struttura_organizzativa',
          ]
        ],
        [
          'name' => 'servizi',
          'value' => [
            'servizi',
          ]
        ],
        [
          'name' => 'novita',
          'value' => [
            'notizia',
            'evento',
          ]
        ],
        [
          'name' => 'didattica',
          'value' => [
            'classe',
          ]
        ]
      ];

      foreach ($bundles as $section_array) {
        $exist = array_search($bundle, $section_array['value']);
        if ($exist !== false) {
          return $section_array['name'];
        }
      }
    }

    return 'vuoto';
  }

}

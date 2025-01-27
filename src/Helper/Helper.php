<?php

namespace Drupal\skenografia\Helper;

use Drupal\Component\Utility\Html;
use Drupal\node\Entity\Node;

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
   *
   * @throws \Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException
   *
   * @throws \Drupal\Component\Plugin\Exception\PluginNotFoundException
   */
  public static function getLocality(): array {
    $data = [];

    // https://www.drupal.org/docs/drupal-apis/entity-api/working-with-the-entity-api#s-query-the-database-for-entities-matching-some-conditions
    $nodeStorage = \Drupal::entityTypeManager()->getStorage('node');
    $ids = $nodeStorage->getQuery()
      ->accessCheck(TRUE)
      ->condition('type', 'luogo')
      ->condition('status', 1)
      ->condition('field_sede_legale', 1)
      ->execute();
    $nodes = $nodeStorage->loadMultiple($ids);

    if (count($nodes) === 1) {
      /** @var Node $sede_legale */
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

  /**
   * @param $opzioni array
   *   - "formato_anno" ("yyyy-yyyy", "yyyy-yy", "yy-yy")
   *      il formato di output dell'anno: 4 o 2 cifre. Default: "yyyy-yyyy"
   *   - "separatore" ("/", " ", "")
   *      il separatore da usare, max un carattere. Default: ""
   *   - "periodo" ("now", "prev", "next")
   *      il periodo da calcolare. Default: "now"
   *
   * @return string
   *   stringa con l'anno scolastico in base al formato
   *     - "2020/2021", "2020/21", "20/21"
   *     - "2020-2021", "2020-21", "20-21"
   *     - "2020 2021", "2020 21", "20 21"
   *     - "20202021", "202021", "2021"
   */
  public static function getAnnoScolastico(array $opzioni = NULL): string {
    // Imposto i valori di default
    $formato_anno = $opzioni['formato_anno'] ?? 'yyyy-yyyy';
    $separatore = $opzioni['separatore'] ?? '/';
    $periodo = $opzioni['periodo'] ?? 'now';

    // Data corrente
    $mese_corrente = (int) date('n'); // Mese (1-12)
    $giorno_corrente = (int) date('j'); // Giorno (1-31)

    // Data corrente espresso in cifre: 31 Agosto = 831
    $data_corrente = ($mese_corrente * 100) + $giorno_corrente;

    // La parte che sta a sinistra dell'AS
    $parte_sinistra = (int) date('Y');

    // In caso bisogna calcolare l'AS precedente
    if ($periodo === 'prev') {
      $parte_sinistra--;
    // In caso bisogna calcolare l'AS successivo
    } elseif ($periodo === 'next') {
      $parte_sinistra++;
    }

    if ($data_corrente <= 831) {
      $parte_sinistra--; // Prima del 31 agosto, l'anno scolastico è quello precedente
    }

    // Calcola la seconda parte dell'AS
    $parte_destra = $parte_sinistra + 1;

    // Formatta gli anni in base al formato specificato
    $parte_sinistra_formattata = ($formato_anno === 'yy-yy')
      ? substr((string) $parte_sinistra, -2)
      : (string) $parte_sinistra;

    $parte_destra_formattata = ($formato_anno === 'yy-yy' || $formato_anno === 'yyyy-yy')
      ? substr((string) $parte_destra, -2)
      : (string) $parte_destra;

    // Costruisce la stringa finale
    return $parte_sinistra_formattata . $separatore . $parte_destra_formattata;
  }

  /**
   * Pulisce un titolo per l'uso in un URL.
   *
   * - Translittera caratteri speciali.
   * - Rimuove caratteri non validi.
   * - Limita a n parole.
   *
   * @param string $title
   *   Il titolo originale.
   * @param int $word_truncate
   *   Eventualmente se bisogna troncare
   * @param string $language
   *   La lingua da usare
   *
   * @return string
   *   Il titolo pulito.
   */
  static function cleanTitleForUrl(string $title, int $word_truncate = 4, string $language = 'it'): string {
    $transliteration = \Drupal::service('transliteration');
    $title = $transliteration->transliterate($title, 'en');

    // Rimuovo i caratteri non alfanumerici suddivido in parole
    $words = preg_split('/\s+/', Html::cleanCssIdentifier($title));

    if ($word_truncate > 0) {
      $words = array_slice($words, 0, $word_truncate);
    }

    // Converto in minuscolo e unisco con "-"
    return strtolower(implode('-', $words));
  }

}

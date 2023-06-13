<?php

namespace Drupal\bi_calendar\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Datetime\DrupalDateTime;

/**
 * Provides an calendar block.
 *
 * @Block(
 *   id = "bi_calendar_hp",
 *   admin_label = @Translation("Events Calendar block"),
 *   category = @Translation("Bootstrap Italia Calendar")
 * )
 */
class CalendarBlock extends BlockBase {

  /**
   * {@inheritdoc}
   */
  public function defaultConfiguration() {
    return [
      'bi_calendar_hp_start' => 0,
      'bi_calendar_hp_stop' => 12,
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function blockForm($form, FormStateInterface $form_state) {
    $form['bi_calendar_hp_start'] = [
      '#type' => 'number',
      '#title' => $this->t('Numero di giorni precedenti ad oggi'),
      '#description' => $this->t('Da quale giorno deve partire la visibilità. Inserire un numero negativo. Es: -4'),
      '#default_value' => $this->configuration['bi_calendar_hp_start'],
    ];
    $form['bi_calendar_hp_stop'] = [
      '#type' => 'number',
      '#title' => $this->t('Numero di giorni dopo oggi'),
      '#description' => $this->t('Fino a quale giorno deve arrivare la visibilità.'),
      '#default_value' => $this->configuration['bi_calendar_hp_stop'],
    ];
    $form['bi_calendar_days_number'] = [
      '#type' => 'number',
      '#title' => $this->t('Numero di giorni da visualizzare'),
      '#description' => $this->t('Numero di card giorno da visualizzare.'),
      '#default_value' => $this->configuration['bi_calendar_days_number'],
    ];

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function blockSubmit($form, FormStateInterface $form_state) {
    $this->configuration['bi_calendar_hp_start']
      = $form_state->getValue('bi_calendar_hp_start');
    $this->configuration['bi_calendar_hp_stop']
      = $form_state->getValue('bi_calendar_hp_stop');
    $this->configuration['bi_calendar_days_number']
      = $form_state->getValue('bi_calendar_days_number');
  }

  /**
   * {@inheritdoc}
   */
  public function build() {
    $start = $this->configuration['bi_calendar_hp_start'];
    $stop = $this->configuration['bi_calendar_hp_stop'];
    /** @var Drupal\Core\Datetime\DateFormatterInterface $date_formatter */
    // $date_formatter = \Drupal::service('date.formatter');
    $utc_timezone = new \DateTimeZone("Europe/Rome");
    $today = date('U');

    $date_time = DrupalDateTime::createFromTimestamp($today, $utc_timezone);
    $today_date = DrupalDateTime::createFromTimestamp($today, $utc_timezone);

    $items = [];

    if ($start < 0) {
      $dateInterval = 'P' . abs($start) . 'D';
      $date_time->sub(new \DateInterval($dateInterval));
    }
    // $month_year = $date_formatter->format($today, 'month_year');
    $month = $date_time->format('F');
    $year = $date_time->format('Y');
    $month_year = $month . ' ' . $year;
    $start_index = $ii = 1;

    for ($i=$start; $i < $stop; $i++) {
      if ($today_date->diff($date_time)->days === 0) {
        $start_index = $ii - 1;
      }
      $items[$i]['day'] = $date_time->format('d');
      $items[$i]['dayname'] = $date_time->format('D');
      $items[$i]['month'] = $date_time->format('m');
      $items[$i]['ext_month'] = $date_time->format('F');
      $nodes = $this->nodeByDay($date_time->format('Y-m-d'));
      $items[$i]['nodes'] = [];
      foreach ($nodes as $nid => $node) {
        $items[$i]['nodes'][] = $node;
      }
      /* Next day step. */
      $date_time->add(new \DateInterval('P1D'));
      $ii++;
    }
    if ($month !== $date_time->format('F')) {
      if ($year === $date_time->format('Y')) {
        $month .= '/' .  $date_time->format('F');
        $month_year = $month . ' '. $year;
      }
      else {
        $month_year = $month . ' '. $year . '/' . $date_time->format('F') . ' ' . $date_time->format('Y');
      }
    }

    $slider_hp = $this->configuration['bi_calendar_hp'] ?? FALSE;

    $build['content'] = [
      '#theme' => 'bi_calendar_block',
      '#month_year' => $month_year,
      '#items' => $items,
      '#start_index' => $start_index,
      '#slider_hp' => $slider_hp,
    ];
    $build['#cache']['max-age'] = 60;

    return $build;
  }

  /**
   * Get calendar nodes.
   *
   * @param string $day
   *
   * @return array
   */
  private function nodeByDay(string $day) {

    $date_start = $day . 'T00:00:00';
    $date_end = $day . 'T23:59:59';
    $query = \Drupal::entityQuery('node')
      ->accessCheck(TRUE)
      ->condition('status', 1)
      ->condition('type', 'evento')
      ->condition('field_data_e_orario_di_inizio', [$date_start, $date_end], 'BETWEEN');
    // $debug = $query->__toString();
    $result = $query->execute();

    return \Drupal::entityTypeManager()->getStorage('node')->loadMultiple($result);
  }

}

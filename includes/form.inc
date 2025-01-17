<?php

/**
 * @file
 * Hook form alter.
 */

use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Template\Attribute;

/**
 * Implements hook_form_alter().
 */
function skenografia_form_alter(&$form, FormStateInterface &$form_state, $form_id):void {
  if (isset($form['#id']) && $form['#id'] == 'views-exposed-form-secondo-livello-servizi-personale-scolastico') {
    $tmp_array = [];
    $tmp_array[1202] = $form['field_tipologia_servizio_target_id']['#options'][1202];
    $tmp_array[1201] = $form['field_tipologia_servizio_target_id']['#options'][1201];
    $form['field_tipologia_servizio_target_id']['#options'] = $tmp_array;
  }

  // Riguardo alle form esposte
  if (isset($form['form_id']) && $form['form_id']['#value'] == 'views_exposed_form') {
//    // Nel caso in cui esiste il submit button
    if (isset($form['actions']['submit'])) {
      if (!isset($form['actions']['submit']['#attributes'])) {
        $form['actions']['submit']['#attributes'] = new Attribute();
        $form['actions']['submit']['#attributes']->addClass(['btn', 'btn-primary']);
      } else {
        if (!isset($form['actions']['submit']['#attributes']['class'])) {
          $form['actions']['submit']['#attributes']['class'] = [];
        }
        $form['actions']['submit']['#attributes']['class'][] = 'btn';
        $form['actions']['submit']['#attributes']['class'][] = 'btn-primary';
      }
    }
    if (isset($form['actions']['reset'])) {
      if (!isset($form['actions']['submit']['#attributes'])) {
        $form['actions']['reset']['#attributes'] = new Attribute();
        $form['actions']['reset']['#attributes']->addClass(['btn', 'btn-primary']);
      } else {
        if (!isset($form['actions']['reset']['#attributes']['class'])) {
          $form['actions']['reset']['#attributes']['class'] = [];
        }
        $form['actions']['reset']['#attributes']['class'][] = 'btn';
        $form['actions']['reset']['#attributes']['class'][] = 'btn-link';
      }
    }
  }
}

<?php

/**
 * @file
 * Theme settings.
 */
use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function skenografia_form_system_theme_settings_alter(array &$form, FormStateInterface $form_state, string $form_id = NULL): void {

  // General "alters" use a form id. Settings should not be set here. The only
  // thing useful about this is if you need to alter the form for the running
  // theme and *not* the theme setting.
  // @see http://drupal.org/node/943212
  if (isset($form_id)) {
    return;
  }

  // Main vertical tabs.
  $form['skenografia'] = [
    '#type' => 'vertical_tabs',
    '#weight' => -12,
  ];
  // Codici --------------------------------------------------------------.
  $form['skenografia_codici'] = [
    '#type' => 'details',
    '#title' => t('Codici identificativi'),
    '#description' => t('Inserisci i codici identificativi della tua scuola.'),
    '#open' => FALSE,
    '#group' => 'skenografia',
    '#weight' => 0,
  ];
  $form['skenografia_codici']['codice_meccanografico'] = [
    '#type' => 'textfield',
    '#title' => t('Codice Meccanografico'),
    '#description' => t("Inserisci il codice meccanografico della tua scuola, in minuscolo."),
    '#placeholder' => t('aabb123456'),
    '#default_value' => theme_get_setting('codice_meccanografico'),
  ];
  $form['skenografia_codici']['codice_fiscale'] = [
    '#type' => 'textfield',
    '#title' => t('Codice fiscale'),
    '#description' => t("Inserisci il codice fiscale della tua scuola, in minuscolo."),
    '#placeholder' => t('12345678901'),
    '#default_value' => theme_get_setting('codice_fiscale'),
  ];
  $form['skenografia_codici']['codice_ipa'] = [
    '#type' => 'textfield',
    '#title' => t('Codice IPA'),
    '#description' => t("Inserisci il codice IPA della tua scuola, in minuscolo."),
    '#default_value' => theme_get_setting('codice_ipa'),
  ];

  // Codici --------------------------------------------------------------.
  $form['skenografia_anagrafica'] = [
    '#type' => 'details',
    '#title' => t('Anagrafica'),
    '#description' => t('Inserisci le informazioni anagrafiche della tua scuola.'),
    '#open' => FALSE,
    '#group' => 'skenografia',
    '#weight' => 1,
  ];
  $form['skenografia_anagrafica']['indirizzo'] = [
    '#type' => 'textfield',
    '#title' => t('Indirizzo'),
    '#placeholder' => t('Via Roma n.1'),
    '#default_value' => theme_get_setting('indirizzo'),
  ];
  $form['skenografia_anagrafica']['cap'] = [
    '#type' => 'textfield',
    '#title' => t('CAP'),
    '#placeholder' => t('12345'),
    '#default_value' => theme_get_setting('cap'),
  ];
  $form['skenografia_anagrafica']['comune'] = [
    '#type' => 'textfield',
    '#title' => t('Comune'),
    '#placeholder' => t('Roma'),
    '#default_value' => theme_get_setting('comune'),
  ];
  $form['skenografia_anagrafica']['provincia'] = [
    '#type' => 'textfield',
    '#title' => t('Provincia'),
    '#placeholder' => t('RM'),
    '#default_value' => theme_get_setting('provincia'),
  ];

  
  $form['#validate'][] = 'skenografia_form_system_theme_settings_validate';
}

/**
 * Implements hook_form_system_theme_settings_validate().
 */
function skenografia_form_system_theme_settings_validate(array &$form, FormStateInterface $form_state): void {
  if (function_exists('file_save_upload')) {
    // Handle file uploads.
    $image_factory = \Drupal::service('image.factory');
    $supported_extensions = $image_factory->getSupportedExtensions();
    $supported_extensions[] = 'svg';
    $validators = ['file_validate_extensions' => [implode(' ', $supported_extensions)]];

    // Check for a new uploaded logo.
    $file = file_save_upload('logo_upload', $validators, FALSE, 0);
    if (isset($file)) {
      // File upload was attempted.
      if ($file) {
        // Put the temporary file in form_values so we can save it on submit.
        $form_state->setValue('logo_upload', $file);
      }
      else {
        // File upload failed.
        $form_state->setErrorByName('logo_upload', t('The logo could not be uploaded.'));
      }
    }
  }
}


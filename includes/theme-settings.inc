<?php

/**
 * @file
 * Theme settings.
 */
use Drupal\Core\Form\FormStateInterface;
use Drupal\node\Entity\Node;

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
  // Media --------------------------------------------------------------.
  $form['skenografia_media'] = [
    '#type' => 'details',
    '#title' => t('Media'),
    '#description' => t('Settings for media module.'),
    '#open' => FALSE,
    '#group' => 'skenografia',
    '#weight' => 2,
  ];
  $form['skenografia_media']['privacy_policy'] = [
    '#type' => 'entity_autocomplete',
    '#title' => t('Privacy policy'),
    '#description' => t('Select privacy policy content.'),
    '#target_type' => 'node',
    '#tags' => TRUE,
    '#selection_handler' => 'default',
    '#default_value' =>
      null !== theme_get_setting('privacy_policy') ?
      Node::load(theme_get_setting('privacy_policy')[0]['target_id']) : 0,
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


<?php

/**
 * Define the Node CSS settings form with content type selection.
 */
function node_css_settings() {
  // Load existing configuration.
  $config = config('node_css.settings');

  // Available themes for CodeMirror.
  $themes = ['default' => 'Default'];  // Start with the default theme.

  // Path to the theme directory.
  $theme_dir = backdrop_get_path('module', 'node_css') . '/codemirror/theme';

  // Check if the directory exists and then scan for theme files.
  if (is_dir($theme_dir)) {
    $theme_files = scandir($theme_dir);

    // Loop through each file and add it to the themes list if it's a CSS file.
    foreach ($theme_files as $file) {
      if (pathinfo($file, PATHINFO_EXTENSION) === 'css') {
        // Get the theme name without the .css extension.
        $theme_name = pathinfo($file, PATHINFO_FILENAME);
        // Convert theme name to title case for display (e.g., "material" becomes "Material").
        $display_name = ucwords(str_replace('-', ' ', $theme_name));
        // Add to the themes array.
        $themes[$theme_name] = $display_name;
      }
    }
  }

  // Select list for choosing the CodeMirror theme.
  $form['codemirror_theme'] = [
    '#type' => 'select',
    '#title' => t('Theme'),
    '#description' => t('Choose a theme for the CSS editor.'),
    '#options' => $themes,
    '#default_value' => $config->get('codemirror_theme') ?: 'default',
  ];

  // Add a height setting for the CSS text area.
  $form['css_textarea_height'] = [
    '#type' => 'number',
    '#title' => t('CSS Textarea Height (rows)'),
    '#description' => t('Set the number of rows for the Node CSS textarea on each node. Default is 10.'),
    '#default_value' => $config->get('css_textarea_height') ?: 10,
    '#min' => 1,
  ];

  // Add position setting for the CSS fieldset.
  $form['css_text_position'] = [
    '#type' => 'select',
    '#title' => t('Position of CSS Editor'),
    '#description' => t('Choose whether to display the CSS editor at the top of the page or between the tabs and the "Save" button.'),
    '#options' => [
      'top' => t('Top (above content)'),
      'bottom' => t('Bottom (between tabs and "Save" button)'),
      'vertical_tab' => t('Vertical Tab'),
    ],
    '#default_value' => $config->get('css_text_position') ?: 'top',
  ];

  // Retrieve all content types.
  $content_types = node_type_get_types();
  $options = [];

  // Prepare options array with machine names and labels.
  foreach ($content_types as $type => $info) {
    $options[$type] = $info->name;
  }

  // Checkbox list for selecting content types.
  $form['enabled_content_types'] = [
    '#type' => 'checkboxes',
    '#title' => t('Enable Node CSS for Content Types'),
    '#description' => t('Select the content types for which the Node CSS module should be active. If no content types are selected, Node CSS will apply to all content types.'),
    '#options' => $options,
    '#default_value' => $config->get('enabled_content_types') ?: [],
  ];


  // Add a default CSS textarea for each content type, shown only if that type is selected.
  foreach ($options as $type => $label) {
    $form['default_css_' . $type] = [
      '#type' => 'textarea',
      '#title' => t('@label Default CSS', ['@label' => $label]),
      '#description' => t('Enter default CSS for @label content type.', ['@label' => $label]),
      '#default_value' => $config->get('default_css_' . $type) ?: $config->get('default'),
      '#attributes' => ['class' => ['codemirror-css-editor']],  // Add class for CodeMirror initialization.
      '#states' => [
        'visible' => [
          ':input[name="enabled_content_types[' . $type . ']"]' => ['checked' => TRUE],
        ],
      ],
    ];
  }

  // Attach CodeMirror to all textareas with the codemirror-css-editor class.
  node_css_attach_codemirror($form, '.codemirror-css-editor');

  // Submit button.
  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Save settings'),
  ];

  return $form;
}

/**
 * Submit handler for the Node CSS settings form.
 */
function node_css_settings_submit($form, &$form_state) {
  // Save selected content types, CodeMirror theme, textarea height, and display position.
  $config = config('node_css.settings');
  $config->set('enabled_content_types', array_filter($form_state['values']['enabled_content_types']));
  $config->set('codemirror_theme', $form_state['values']['codemirror_theme']);
  $config->set('css_textarea_height', $form_state['values']['css_textarea_height']);
  $config->set('css_text_position', $form_state['values']['css_text_position']);  // Save position setting.

  // Save each default CSS value for the selected content types.
  foreach ($form_state['values']['enabled_content_types'] as $type => $enabled) {
    if ($enabled) {
      $config->set('default_css_' . $type, $form_state['values']['default_css_' . $type]);
    }
  }

  $config->save();

  // Display a status message.
  backdrop_set_message(t('The Node CSS settings have been saved.'));
}




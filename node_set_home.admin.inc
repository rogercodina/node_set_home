<?php

/**
 * @file
 * Administration page.
 */

/**
 * Configuration form render.
 */
function node_set_home_admin_settings() {

  $form['node_set_home_nodelist'] = array(
    '#type' => 'textarea',
    '#title' => t('List of nodes selectable for homepage. Just write the nid (node ID).'),
    '#description' => t('One node per line.'),
    '#rows' => 10,
    '#cols' => 40,
    '#default_value' => variable_get('node_set_home_nodelist', ''),
  );

  return system_settings_form($form, TRUE);
}

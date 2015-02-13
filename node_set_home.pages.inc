<?php

/**
 * @file
 * Node set home.
 */

/**
 * Displays page where user can select home page.
 */
function node_set_home_show_home_selector_page() {
  global $user;

  $nodes = variable_get('node_set_home_nodelist', '');

  if (!empty($nodes)) {
    $form = drupal_get_form('node_set_home_select_homepage_form');
    $output = drupal_render($form);
  }
  else {
    $output = '<p>' . t('No selectable nodes found for being marked as the homepage.') . '</p>';

    // Warning message for administrators.
    if (in_array('administrator', $user->roles)) {
      drupal_set_message(t('Go to "admin/config/system/node_set_home" and set some nodes to be selectable for homepage.'), 'warning');
    }
  }

  return $output;
}

/**
 * Creates a form for selecting homepage.
 */
function node_set_home_select_homepage_form($form, &$form_state) {
  $nodes = variable_get('node_set_home_nodelist', '');
  $nodes = explode("\r\n", $nodes);

  // Build node list.
  $list = array('' => 'Undefined');
  foreach ($nodes as $nid) {
    if(!empty($nid)) {
      $node = node_load($nid);
      $list[$nid] = $node->title;
    }
  }

  // Build home page selector.
  $current_home = variable_get('site_frontpage', '');
  $default = str_replace('node/', '', $current_home);
  $form['site_frontpage'] = array(
    '#type' => 'select',
    '#title' => t('Home page'),
    '#options' => $list,
    '#default_value' => $default,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );

  $form['#submit'][] = 'node_set_home_select_homepage_form_submit';
  return $form;
}

/**
 * Submit handler.
 */
function node_set_home_select_homepage_form_submit($form, &$form_state) {
  if (!empty($form_state['values']['site_frontpage'])) {
    variable_set('site_frontpage', 'node/' . $form_state['values']['site_frontpage']);
    drupal_set_message(t('New homepage has been set'));
  }
}

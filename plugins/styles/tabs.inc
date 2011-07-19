<?php


/**
 * @file
 * Definition of the 'Tabs' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('Tabs'),
  'description' => t('Show panel panes in a region as tabs.'),
  'render region' => 'panels_tabs_style_render_region',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_tabs_style_render_region($vars) {
  $display = $vars['display'];
  $region_id = $vars['region_id'];
  $owner_id = $vars['owner_id'];
  $panes = $vars['panes'];

  drupal_add_library('system', 'jquery.ui');

  $tab_id = 'tabs-' . $owner_id . '-' . $region_id;

  $output = array(
    '#prefix' => '<div id="' . $tab_id . '">',
    '#suffix' => '</div>',
  );

  // Get the pane titles.
  $items = array();
  $delta = 1;
  foreach ($display->panels[$region_id] as $pane_id) {
    $pane = $display->content[$pane_id];
    $content = ctools_content_render($pane->type, $pane->subtype, $pane->configuration);
    $items[] = '<a href="#"'. $tab_id . '-' . $delta .'>' . $content->title . '</a>';
    ++$delta;
  }

  $output['tabs_title'] = array('#theme' => 'item_list', '#items' => $items);

  $items = array();
  $delta = 1;
  foreach ($panes as $pane_id => $item) {
    $output['tabs_content'][$pane_id] = array(
      '#prefix' => '<div id="' . $tab_id . '-' . $delta . '">',
      '#suffix' => '</div>',
      '#markup' => $item,
    );
    ++$delta;
  }

  dpm($output);

  // FIXME: Return as array.
  return drupal_render($output);
}

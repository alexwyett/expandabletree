<?php

/**
 * Custom search form configuration
 * 
 * @param array $form
 * @param array $form_state
 * 
 * @return array
 */
function expandabletree_config_form($form, &$form_state)
{
    $form['expandabletree_elements'] = array(
        '#tree' => true,
        '#theme' => 'expandabletree'
    );
    
    if (isset($form_state['expandabletree_elements'])) {
        $defaults = $form_state['expandabletree_elements'];
    } else {
        $defaults = expandabletree_get_elements();
    }
    
    if (isset($form_state['append']) && $form_state['append'] == true) {
        // push element into array
        $defaults[] = array(
            'weight' => 0
        );
    }
    
    $form_state['expandabletree_elements'] = $defaults;
    
    $form['actions']['add_item'] = array(
        '#type' => 'submit',
        '#value' => (count($defaults) == 0) ? 'Add item' : 'Add another',
        '#submit' => array('expandabletree_form_add_item'),
        '#limit_validation_errors' => array(),
        '#weight' => 9999
    );
    
    foreach ($defaults as $i => $element) {
        $pointer = $i;
        $form['expandabletree_elements'][$i] = array(
            '#type' => 'fieldset',
            '#title' => 'Search element ' . ($pointer + 1)
        );
        
        $form['expandabletree_elements'][$i]['field'] = array(
            '#type' => 'textfield',
            '#title' => 'Field',
            '#default_value' => isset($element['field']) ? $element['field'] : '',
            '#required' => true
        );
        
        $form['expandabletree_elements'][$i]['weight'] = array(
            '#type' => 'textfield',
            '#title' => 'Weight',
            '#default_value' => isset($element['weight']) ? $element['weight'] : '0',
            '#size' => 3,
            '#attributes' => array('class' => array('item-row-weight')),
        );

        $form['expandabletree_elements'][$i]['remove_item'] = array(
            '#type' => 'submit',
            '#value' => t('Remove item'),
            '#submit' => array('expandabletree_form_remove_item'),
            '#limit_validation_errors' => array(),
            '#attributes' => array(
                'button_index' => $i
            )
        );
    }
    
    return system_settings_form($form);
}

/**
 * Increase the number of items in the form
 * 
 * @param array $form
 * @param array $form_state
 * 
 * @return void
 */
function expandabletree_form_add_item($form, &$form_state)
{
    $form_state['append']  = TRUE;
    $form_state['rebuild'] = TRUE;
}

/**
 * Increase the number of items in the form
 * 
 * @param array $form
 * @param array $form_state
 * 
 * @return void
 */
function expandabletree_form_remove_item($form, &$form_state)
{
    if($form_state['clicked_button']) {
        $defaults = $form_state['expandabletree_elements'];
        if (isset($defaults[$form_state['clicked_button']['#attributes']['button_index']])) {
            unset($defaults[$form_state['clicked_button']['#attributes']['button_index']]);
        }
        $form_state['expandabletree_elements'] = $defaults;
        $form_state['append']  = FALSE;
        $form_state['rebuild'] = TRUE;
    }
}
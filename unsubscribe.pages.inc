<?php
/**
 * @file
 * Defines form and page callbacks for unsubscribe module.
 */

/**
 * Form constructor for unsubscribe settings page.
 */
function unsubscribe_settings_form($form, &$form_state) {
  $config = config('unsubscribe.settings');

  $form['unsubscribe_append'] = array(
    '#type' => 'checkbox',
    '#title' => t('Append unsubscribe link to all outgoing emails'),
    '#default_value' => $config->get('append'),
  );
  $form['exemptions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Module Exemptions'),
    '#description' => t("These modules will be exempt from the unsubscribe module's blocking mechanism. Emails sent by select modules will still be sent to unsubscribed users."),
  );
  $form['exemptions']['unsubscribe_exempt_modules'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Exempt modules'),
    '#options' => backdrop_map_assoc(module_implements('mail')),
    '#default_value' => $config->get('exempt_modules'),
    '#description' => t('Developers: you can programatically alter this list using hook_unsubscribe_exemptions_alter().'),
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Submit handler for unsubscribe settings page.
 */
function unsubscribe_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $config = config('unsubscribe.settings');
  $config->set('append', (bool) $values['unsubscribe_append']);
  $config->set('exempt_modules', $values['unsubscribe_exempt_modules']);
  $config->save();

  backdrop_set_message('');
}

/**
 * Form constructor for unsubscribe form.
 */
function unsubscribe_unsubscribe_form($form, &$form_state) {
  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Your email address'),
    '#description' => t('Enter your email address to unsubscribe from email communications.'),
    '#default_value' => !empty($_GET['mail']) ? $_GET['mail'] : '',
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Unsubscribe'),
  );
  return $form;
}

/**
 * Form validation handler for unsubscribe_unsubscribe_form().
 */
function unsubscribe_unsubscribe_form_validate($form, &$form_state) {
  $mail = $form_state['values']['mail'];

  // Validate email address.
  if (!valid_email_address($mail)) {
    form_set_error('mail', t('The e-mail address you specified is not valid.'));
  }
  else {
    // Check to see that email address belongs to an existing user.
    if ($account = user_load_by_mail($mail)) {
      // Check to see if this user has already unsubscribed.
      if (unsubscribe_user_check($account)) {
        form_set_error('mail', t('The e-mail address that you specified has already been unsubscribed.'));
      }
    }
    else {
      form_set_error('mail', t('The e-mail address that you specified is not in our database.'));
    }
  }
}

/**
 * Form submission handler for unsubscribe_unsubscribe_form().
 */
function unsubscribe_unsubscribe_form_submit($form, &$form_state) {
  $mail = $form_state['values']['mail'];
  $account = user_load_by_mail($mail);
  unsubscribe_user_add($account->uid);
}

<?php

/**
 * Form callback for unsubscribe form.
 */
function unsubscribe_unsubscribe_form($form, &$form_state) {
  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Your email address'),
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
 * Form validation callback for unsubscribe form.
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
      if (unsubscribe_user_check(array('mail' => $mail))) {
        form_set_error('mail', t('The e-mail address that you specified has already been unsubscribed.'));
      }
    }
    else {
      form_set_error('mail', t('The e-mail address that you specified is not in our database.'));
    }
  }
}

/**
 * Form submit callback for unsubscribe form.
 */
function unsubscribe_unsubscribe_form_submit($form, &$form_state) {
  $account = user_load_by_mail($mail);
  unsubscribe_user_add($account->uid);
}
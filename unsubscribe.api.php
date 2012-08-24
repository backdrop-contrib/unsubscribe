<?php
/**
 * @file
 * This file contains API documentation for the unsubscribe module. Note that
 * all of this code is merely for example purposes, it is never executed when
 * using the unsubscribe module.
 */

/**
 * Alter the list of unsubscribe module exemptions.
 *
 * @param array $exemptions
 *   A single-dimensional array comprised of module machine-names.
 */
function hook_unsubscribe_exemptions_alter(&$exemptions) {
  // Add new exception for custom_module.
  $exemptions[] = 'custom_module';

  // Remove system module exemption.
  unset($exemptions['system']);
}

/**
 * Allows modules to override unsubscribe's blocking function.
 *
 * You might ask "Why would I need this? I can just implement hook_mail_alter()
 * to modify $message." Well, this hook is always called AFTER exemptions have 
 * been checked, and unsubscribe has done its work. This means that you don't
 * need to worry about module weights.
 *
 * @param array $message
 *   An associative array containing the message to be sent.
 */
function hook_unsubscribe_override(&$message) {
  // Exempt any mail sent by user 0.
  if (user_load_by_mail($message['from'])->uid == 0) {
    $message['send'] = TRUE;
  }
}
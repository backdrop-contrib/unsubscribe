<?php
/**
 * @file
 * This file contains API documentation for the unsubscribe module. Note that
 * all of this code is merely for example purposes, it is never executed when
 * using the unsubscribe module.
 */

/**
 * Allows modules to override unsubscribe's blocking function AFTER the block as occured.
 */
function hook_unsubscribe_override(&$message) {
  // More complex exemptions. E.g., exempt any mail sent by user 0.
  if (user_load_by_mail($message['from'])->uid == 0) {
    $message['send'] = TRUE;
  }
}

/**
 *
 */
function hook_unsubscribe_exemptions_alter(&$exemptions) {
  // Add more exceptions.
  $exemptions[] = 'my_module';

  // Remove exemptions.
  unset($exemptions['system']);
}
<?php

/**
 * Allows modules to alter unsubscribes blocking of emails to unsubscribed users.
 */
function hook_unsubscribe_mail_block(&$message, &$exemptions, &$block) {
  // Add more exceptions.
  $exemptions[] = 'my_module';

  // Remove exemptions.
  unset($exemptions['system']);

  // More complex exemptions. E.g., exempt any mail sent by user 0.
  if (user_load_by_mail($message['from'])->uid == 0) {
    $block = FALSE;
  }

}
Description
-----------
This is a general purpose module that allows users to unsubscribe from all
email communications sent by Backdrop.

The module design is very basic. When a user unsubscribes, they are added to an
"unsubscribe list," which is stored in the database. Whenever Backdrop sends
mail, the unsubscribe module will check to see if the recipient is on the
unsubscribe list. If so, the email is blocked. You can exempt specific modules
from this blocking via the configuration page. You can also use hooks to alter
exemptions, or override the blocking.

Requirements
------------
Backdrop 1.x

Installation
-----------
Download the module and enable it!

API Integration
---------------
The unsubscribe module provides an API for modifying module exemptions,
overriding email blocking, and reacting to unsubscribe events.

More information about Unsubscribe's hooks can be found in
unsubscribe.api.php file included with this module.

Theming
-------
The unsubscribe module allows for the unsubscribe link to me themed
via theme_unsubscribe().

License
-------
This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainers
-------------------
- Dan Boulet (https://github.com/dboulet)

Credits
-------
- Ported to Backdrop CMS by Dan Boulet (https://github.com/dboulet).
- Originally written for Drupal by Matthew Grasmick (https://www.drupal.org/u/grasmash).

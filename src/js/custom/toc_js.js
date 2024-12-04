/**
 * @file
 * Toc_js customization.
 */
((Drupal, once) => {
  Drupal.behaviors.skenografia_toc_js_update = {
    attach(context) {
      once('skenografia_toc_js_update', '.toc-js', context).forEach((elt) => {
        const navUl = elt.querySelector('.toc-js nav ul');
        if (navUl) {
          navUl.setAttribute('data-element', 'page-index');
        }
      });
    },
  };
})(Drupal, once);

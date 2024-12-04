(function () {
  'use strict';

  Drupal.behaviors.mainMenuClose = {
    attach: function (context, settings) {
      document.addEventListener('DOMContentLoaded', function () {
        const e = document.querySelector('.hamburger');
        document.addEventListener('keyup', function (event) {if (event.key === 'Escape') {if (e.classList.contains('is-active')) {e.click();}}});
      });
    }
  };

})(Drupal);

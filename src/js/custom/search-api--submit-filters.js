(function (Drupal, once) {
  'use strict';

  Drupal.behaviors.searchAPISubmitFilters = {
    attach: function (context, settings) {
      // Tutti i submit nella form di ricerca o nelle form di ricerca.
      let submitButtons = once('searchAPISubmitFilters', context.querySelectorAll('[data-search-api-submit-filters]'));

      // Intercetto l'evento click sui submit.
      submitButtons.forEach(function(button) {
        button.addEventListener('click', function(event) {
          // Evito il submit per poter fare cose.
          event.preventDefault();

          // La form su cui operare
          let form = button.closest('form');

          if (form) {
            // Prendo i valori dei filtri dagli attributi del submit.
            let values = JSON.parse(button.getAttribute('data-search-api-submit-filters'));

            // Il nodo, o i nodi, a cui devo aggiungere le informazioni sui filtri da applicare.
            let filters = form.querySelectorAll('[data-search-filter-id]');

            // Aggiunta dei filtri.
            filters.forEach(function(filter) {
              values.forEach(function(value) {
                let input = document.createElement('input');
                input.type = 'hidden';
                input.name = 'f[]';
                input.value = value;
                filter.parentNode.insertBefore(input, filter);
              });
            });

            form.submit();
          }

        });
      });
    }
  };

})(Drupal,once);

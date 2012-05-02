var nbar = require('./build/Release/nbar_node.node');

nbar.start();

setInterval(function() {
  var now = new Date(),
      today = now.getFullYear() + '-' + (now.getMonth() + 1) + '-' + now.getDay(),
      time = now.getHours() + ':' + now.getMinutes() + ':' + now.getSeconds();

  console.log('[1] ' + time );

}, 1000);

/*
var nbar = require('nbar').start().size(1);

function update() {
  var now = new Date(),
      today = now.getFullYear() + '-' + (now.getMonth() + 1) + '-' + now.getDay(),
      time = now.getHours() + ':' + now.getMinutes() + ':' + now.getSeconds();

  nbar.clear()
      .add('[1] ' + today + ' ' + time );
}

setInterval(update, 1000);
*/

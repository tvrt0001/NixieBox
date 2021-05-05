/*
 * Magic Mirror
 * Module: NixieGame
 * Developed By Thomas Tiveron
 * Ceated on February 1st 2021
 */

const NodeHelper = require('node_helper');
const request = require('request');


module.exports = NodeHelper.create({

	start: function() {
		console.log("Starting node_helper for: " + this.name);
		this.alerts = {};
	},

	getATM: function(url) {
		request({
			url: url,
			method: 'GET'
		}, (error, response, body) => {
			if (!error && response.statusCode == 200) {
				var result = JSON.parse(body).results; // Parsing an array
				console.log(response.statusCode + result);
					this.sendSocketNotification('ATM_RESULT', result);
			}
		});
	},

	socketNotificationReceived: function(notification, payload, sender) {
		if (notification === 'GET_ATM') {
			this.getATM(payload);
		}
		if (notification === "SHOW_ALERT") {
			if (payload.type === "notification") {
				this.show_notification(payload);
			} else if (notification === "HIDE_ALERT") {
				this.hide_alert(sender);
			}
		}		
	},


	/*

	show_notification: function (message) 
	{
		if (this.config.effect === "slide") {
			this.config.effect = this.config.effect + "-" + this.config.position;
		}

		let msg = "";
		if (message.title) {
			msg += "<span class='thin dimmed medium'>" + message.title + "</span>";
		}
		if (message.message) {
			if (msg !== "") {
				msg += "<br />";
			}
			msg += "<span class='light bright small'>" + message.message + "</span>";


		}

		// new NotificationFx({
		// 	message: msg,
		// 	layout: "growl",
		// 	effect: this.config.effect,
		// 	ttl: message.timer !== undefined ? message.timer : this.config.display_time
		// }).show();
	}
*/

});


/*
**COULD Iterate through all elemets

			function extractJSON(obj, indent) {
			for (var i in obj) {
				if (Array.isArray(obj[i]) || typeof obj[i] === 'object') {
				console.log(indent + i + ' is array or object');
				extractJSON(obj[i], indent + ' > ' + i + ' > ');
				} else {
				console.log(indent + i + ': ' + obj[i]);
				}
			}
			}
			extractJSON(jsonobject, "$$");
*/
/*
 * Magic Mirror
 * Module: NixieGame
 * Developed By Thomas Tiveron
 */


Module.register("NixieGame", {

    // Module config defaults.
    defaults: {
        multipleChoice: "Yes", // No = no multiple choice answers appear
        useHeader: true, // false if you don't want a header
        header: "Nixie's Trivia Game", // Any text you want
        maxWidth: "250px",
        rotateInterval: 30 * 1000, // 20 secs to think then answer appears for 10 secs
        animationSpeed: 3000, // fade in and out speed
        initialLoadDelay: 4250,
        retryDelay: 2500,
        updateInterval: 25 * 60 * 1000, // API limits 50 questions per call 
        localDB: false,  
        // false get questions from  "https://opentdb.com/api.php?amount=50&type=multiple"
        // True get questions from  "http://localhost:port/modules/NixieGame/Questions.json"
    },

    getStyles: function () {
        return ["NixieGame.css"];
    },

    start: function () {
        Log.info("Starting module: " + this.name);

        requiresVersion: "2.1.0",
        this.url = "https://opentdb.com/api.php?amount=50&type=multiple";
        this.alerts = {};
        this.ATM = [];
        this.activeItem = 0;
        this.rotateInterval = null;
        this.scheduleUpdate();
    },

    getDom: function () {

        var wrapper = document.createElement("div");
        wrapper.className = "wrapper";
        wrapper.style.maxWidth = this.config.maxWidth;

        if (!this.loaded) {
            wrapper.innerHTML = "Nixie's Trivia Game!";
            wrapper.classList.add("bright", "light", "large");
            return wrapper;
        }

        if (this.config.useHeader != false) {
            var header = document.createElement("header");
            header.classList.add("large", "bright", "light", "header");
            header.innerHTML = this.config.header;
            wrapper.appendChild(header);
        }

        var ATMKeys = Object.keys(this.ATM);
        if (ATMKeys.length > 0) {
            if (this.activeItem >= ATMKeys.length) {
                this.activeItem = 0;
            }

            var ATM = this.ATM[ATMKeys[this.activeItem]];

            var top = document.createElement("div");
            top.classList.add("list-row");

            var category = document.createElement("div");
            category.classList.add("medium", "bright", "category");
            category.innerHTML = "Category: &nbsp" + ATM.category; // ATM.category;
            wrapper.appendChild(category);

            var difficulty = document.createElement("div");
            var str = ATM.difficulty;
            var res = str.toUpperCase();
            difficulty.classList.add("medium", "bright", "difficulty");
            difficulty.innerHTML = "Difficulty: &nbsp" + res; // ATM.difficulty;
            wrapper.appendChild(difficulty);

            var question = document.createElement("div");
            question.classList.add("large", "bright", "question");
            question.innerHTML = ATM.question; // ATM.question;
            wrapper.appendChild(question);
            
            var spacer = document.createElement("div");
            spacer.innerHTML = "&nbsp";
            wrapper.appendChild(spacer);

/*
START ANSWERS SECTION
 - Loop Through Answers & Randomize Correct Answer index
 */

            var multipleChoice = this.config.multipleChoice
            
            var cAnswer = ATM.correct_answer;
            var cAnswerIndex = Math.floor(Math.random() * 4); 
            ATM.incorrect_answers.splice(cAnswerIndex.valueOf(),  0, cAnswer);
            var count = 0;

            console.log("valof: " + cAnswerIndex.valueOf());
            console.log("cAnswerIndex:" + cAnswerIndex);
            console.log("array:" + ATM.incorrect_answers);

            var answers = document.createElement("div");
            answers.classList.add("large", "bright", "answer");              

            for(i in ATM.incorrect_answers)
            {
                console.log("inc_ans: " + ATM.incorrect_answers[i]);
                var iAnswer = ATM.incorrect_answers[i];
                var answer = document.createElement("div");
                answer.classList.add("large", "bright", "answer");                  

                if(count == cAnswerIndex) {
                    console.log("count: " + count + " == cAnswerIndex: " + cAnswerIndex);
                    console.log("iAnswer:" + iAnswer);
                    answer.innerHTML = count + ": &nbsp;&nbsp" + iAnswer;
                    setTimeout(function () { 
                        answer.classList.add("blurEffect");
                        answer.innerHTML = "X: &nbsp;&nbsp" + iAnswer;
                    }, 20 * 1000);
                }
                else {
                    answer.innerHTML = count + ": &nbsp;&nbsp" + iAnswer;
                }

                answers.appendChild(answer);
                count++;
            }

            wrapper.appendChild(answers);
            count = 0;

            console.log("END LOOP: " + answers.innherHTML)
/*
END ANSWERS SECTION
*/
            var spacer = document.createElement("div");
            spacer.innerHTML = "&nbsp";
            wrapper.appendChild(spacer);

            var correctAnswer = document.createElement("div");
            correctAnswer.classList.add("large", "bright", "correct");
            setTimeout(function () { correctAnswer.innerHTML = ATM.correct_answer }, 20 * 1000);
            wrapper.appendChild(correctAnswer);

/*
Show Players Section
*/          
            var showPlayersInfo = false;

            if(showPlayersInfo)
            {
                var players = document.createElement("div");
                players.classList.add("large", "bright", "players");
                
                var player = document.createElement("div");
                player.classList.add("large", "bright", "player"); //, "blurEffect");
                //setTimeout(function () { }, 20 * 1000);
                player.innerHTML = player.innerHTML = "Player #1: &nbsp;&nbsp" + 1;
                players.appendChild(player);

                var player = document.createElement("div");
                player.classList.add("large", "bright", "player");            
                player.innerHTML = "Player #2: &nbsp;&nbsp" + 2; 
                players.appendChild(player);
                
                wrapper.appendChild(players);
            }

/*
End Players Section
*/
        }
        return wrapper;
    },

    processATM: function (data) {
        this.today = data.Today;
        this.ATM = data;
        console.log(this.ATM); // checking my data
        this.loaded = true;
    },

    scheduleCarousel: function () {
        this.rotateInterval = setInterval(() => {
            this.activeItem++;
            this.updateDom(this.config.animationSpeed);
        }, this.config.rotateInterval);
    },

    scheduleUpdate: function () {
        setInterval(() => {
            this.getATM();
        }, this.config.updateInterval);
        this.getATM(this.config.initialLoadDelay);
        var self = this;
    },

    getATM: function () {
        this.sendSocketNotification('GET_ATM', this.url);
    },

    socketNotificationReceived: function (notification, payload) {
        if (notification === "ATM_RESULT") {
            this.processATM(payload);
            if (this.rotateInterval == null) {
                this.scheduleCarousel();
            }
            this.updateDom(this.config.animationSpeed);
        }
        this.updateDom(this.config.initialLoadDelay);
    },

    notificationReceived: function (notification, payload) {
        if (notification === 'HIDE_TRIVIA') {
            this.hide(1000);
        } else if (notification === 'SHOW_TRIVIA') {
            this.show(1000);
        }
    },

    processATM: function (data) {
        this.today = data.Today;
        this.ATM = data;
        console.log(this.ATM); // checking my data
        this.loaded = true;
    },    

});


/*MESSAGE API */

// ALERT
// http://nixie.tivtronics.com:8282/api/module/alert/showalert?message=You%20Suck%20GolfBalls&timer=2000

// Notification
//

// sendResponset
//  http://nixie.tivtronics.com:8282/api/module/NixieGame/sendResponset?gpid=00&button=01&timestamp=00000


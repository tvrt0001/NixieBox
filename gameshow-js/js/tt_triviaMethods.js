/********************************
 *  trivia Methods
 * *****************************/

/**
 * Retrieves random trivia from the Open Trivia DB
 * @param {{amount: Number, difficulty: String, category: String, type: String, token: String}} options Options to get trivia questions with. amount: integer amount of questions to retrieve. difficulty: easy, medium, or hard. category: category of questions. type: multiple or boolean. token: session token to prevent duplicate trivia.
 * @returns {Promise<JSON>}
 */
exports.getTrivia = async function (options = {}) {
    var amount = options.amount !== undefined ? options.amount : 1;
    var difficulty = options.difficulty !== undefined ? options.difficulty : 'medium';
    var category = options.category !== undefined ? options.category : 'any';
    var type = options.type !== undefined ? options.type : 'multiple';
    var token = options.token !== undefined ? options.token : '';

    return new Promise(async (resolve, reject) => {
        try {
            const maxCategories = await axios.get('https://opentdb.com/api_category.php');
            const cateID = methods.getTriviaCategoryID(category, maxCategories.data.trivia_categories[maxCategories.data.trivia_categories.length - 1].id);
            const pamount = methods.getTriviaAmount(amount);
            const ptype = methods.getTriviaType(type);
            const pdifficulty = methods.getTriviaDifficulty(difficulty);

            var finalParams = {
                amount: pamount
            }

            if (cateID !== '') {
                finalParams.category = cateID
            }
            if (pdifficulty !== '') {
                finalParams.difficulty = pdifficulty
            }
            if (ptype !== '') {
                finalParams.type = ptype
            }
            if (token !== '') {
                finalParams.token = token
            }

            const result = await axios.get('https://opentdb.com/api.php', {
                params: finalParams
            });

            if (result.data.response_code !== 0) {
                reject(new Error('Response code ' + result.data.response_code + ': ' + methods.getReponseError(result.data.response_code)));
            }
            else {
                var filteredResult = JSON.parse(JSON.stringify(result.data.results)
                    .replace(/&quot;/g, '\\"')
                    .replace(/&#039;/g, "'")
                    .replace(/&amp;/g, '&')
                    .replace(/&acute;/g, '`')
                    .replace(/&eacute;/g, 'é')
                    .replace(/&oacute;/g, 'ó')
                    .replace(/&pound;/g, '£')
                    .replace(/&aacute;/g, 'á')
                    .replace(/&Aacute;/g, 'Á')
                    .replace(/&ntilde;/g, 'ñ')
                    .replace(/&rdquo;/g, '\\"')
                    .replace(/&ouml;/g, 'ö')
                );
                resolve(filteredResult);
            }

        }
        catch (err) {
            reject(err);
        }
    });
}

/**
 * Retrieves a session token
 * @returns {Promise<String>} Token
 */
exports.getToken = async function () {
    return new Promise(async (resolve, reject) => {
        try {
            const result = await axios.get('https://opentdb.com/api_token.php?command=request');

            if (result.data.response_code !== 0) {
                reject(new Error('Response code ' + result.data.response_code + ': ' + result.data.response_message));
            }
            else {
                resolve(result.data.token);
            }
        }
        catch (err) {
            reject(err);
        }
    })
}

/**
 * Resets a session token
 * @param {String} token Token to reset session for.
 * @returns {Promise<Boolean>} Success
 */
exports.resetToken = async function (token) {
    const result = await axios.get(`https://opentdb.com/api_token.php?command=reset&token=${token}`)

    if (result.data.response_code !== 0) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * Returns all categories along with their ID
 * @returns {Promise<Object>}
 */
exports.getCategories = async function () {
    const results = await axios.get('https://opentdb.com/api_category.php');

    return results.data.trivia_categories;
}

/**
 * Returns the total question account for a category
 * @param {String} category Category to get count for.
 * @returns {Promse<Object>}
 */
exports.getQuestionCount = function (category) {
    return new Promise(async (resolve, reject) => {
        try {
            const maxCategories = await axios.get('https://opentdb.com/api_category.php');
            const cateID = methods.getTriviaCategoryID(category, maxCategories.data.trivia_categories[maxCategories.data.trivia_categories.length - 1].id);

            const questionCount = await axios.get(`https://opentdb.com/api_count.php?category=${cateID}`);

            resolve(questionCount.data.category_question_count);
        }
        catch (err) {
            reject(err);
        }
    });
}

exports.getTriviaCategoryID = function (category, maxCategory) {
    if (parseInt(category) >= 9 && parseInt(category) <= maxCategory) {
        return category;
    }

    switch (category) {
        case 'any': return '';
        case 'general': return 9;
        case 'books': return 10;
        case 'film': return 11;
        case 'music': return 12;
        case 'theatre': return 13;
        case 'television': return 14;
        case 'videogames': return 15;
        case 'boardgames': return 16;
        case 'science': return 17;
        case 'computers': return 18;
        case 'mathematics':
        case 'math': return 19;
        case 'mythology': return 20;
        case 'sports': return 21;
        case 'geography': return 22;
        case 'history': return 23;
        case 'politics': return 24;
        case 'art': return 25;
        case 'celebrities': return 26;
        case 'animals': return 27;
        case 'vehicles': return 28;
        case 'comics': return 29;
        case 'gadgets': return 30;
        case 'anime': return 31;
        case 'cartoons': return 32;

        default: throw new Error('Cannot find specified category');
    }
}

exports.getTriviaType = function (type) {
    switch (type) {
        case 'any': return '';
        case 'choice':
        case 'multiple': return 'multiple';
        case 'truefalse':
        case 'boolean': return 'boolean';

        default: throw new Error(type + ' is not a valid type. Type must either be multiple (multiple choice), or boolean (true/false)');
    }
}

exports.getTriviaDifficulty = function (difficulty) {
    switch (difficulty) {
        case 'any': return '';
        case 'easy': return 'easy';
        case 'medium': return 'medium';
        case 'hard': return 'hard';

        default: throw new Error(difficulty + ' is not a valid difficulty. Difficulty must either be easy, medium, or hard');
    }
}

exports.getTriviaAmount = function (amount) {
    if (typeof amount !== 'number' || amount < 1 || amount > 50) {
        throw new Error('Amount must be a value between 1 and 50');
    }
    else {
        return amount;
    }
}

exports.getTriviaReponseError = function (code) {
    switch (code) {
        case 1: return "The API doesn't have enough questions for your query.";
        case 2: return "Invalid parameter(s). Arguments passed aren't valid.";
        case 3: return "Invalid session token.";
        case 4: return "Session token has retrieved all possible questions for the specified query. Reset the token.";

        default: return "An error has occured in the API";
    }
}
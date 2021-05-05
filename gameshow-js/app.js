const newToken = await opentdb.getToken();

var options = {
      amount: 2,
      category: 'science',
      difficulty: 'easy',
      type: 'multiple',
      token: newToken
}

const uniqueTrivia = await opentdb.getTrivia(options);
console.log(uniqueTrivia);
//////////////////////////////////////////

const opentdb = require('opentdb-api');

var options = {
      amount: 2,
      category: 'science',
      difficulty: 'easy',
      type: 'multiple'
}

opentdb.getTrivia(options).then(result => { console.log(result); }

);

// =>[ { category: 'Science & Nature',
// =>    type: 'multiple',
// =>    difficulty: 'easy',
// =>    question: 'Alzheimer\'s disease primarily affects which part of the human body?',
// =>    correct_answer: 'Brain',
// =>    incorrect_answers: [ 'Lungs', 'Skin', 'Heart' ] },
// =>  { category: 'Science & Nature',
// =>    type: 'multiple',
// =>    difficulty: 'easy',
// =>    question: 'What animal takes part in Schrödinger\'s most famous thought experiment?',
// =>    correct_answer: 'Cat',
// =>    incorrect_answers: [ 'Dog', 'Bat', 'Butterfly' ] } ]

/********************************
 * Merged Lists
 * *****************************/

const merge = (currentList, newList) => {
      // We take the currentList at first load, and the "load more" list.
      // First we just merge it by spread operator => [...currentList, ...newList]
      // After that we use `Array.prototype.reduce` to generate a new array,
      // Which is merged and grouped by date.
      const merged = [...currentList, ...newList].reduce((acc, item) => {
            // Condition 1: just push the item to the new empty array, or
            // if the last item in `acc` doesn't have the same date with the current item
            if (!acc.length || acc[acc.length - 1].date !== item.date) {
                  acc.push(item);
            } else {
                  // Condition 2: if they have the same date, we merge it. 🤝
                  const lastItem = acc[acc.length - 1];
                  const mergedDate = [...lastItem.transactions, ...item.transactions];
                  lastItem.transactions = mergedDate;
            }
            return acc;
      }, []);
      return merged;
};

const result = await fakeAPIRequest(page);

setMergedList((prevList) =>
      merge(cloneDeep(prevList), cloneDeep(result.items))
);

/********************************
 * Fetch Random Users
 * *****************************/

function createNode(element) {
      return document.createElement(element);
}

function append(parent, el) {
      return parent.appendChild(el);
}

const ul = document.getElementById('authors');
const url = 'https://randomuser.me/api/?results=10';

fetch(url)
      .then((resp) => resp.json())
      .then(function (data) {
            let authors = data.results;
            return authors.map(function (author) {
                  let li = createNode('li');
                  let img = createNode('img');
                  let span = createNode('span');
                  img.src = author.picture.medium;
                  span.innerHTML = `${author.name.first} ${author.name.last}`;
                  append(li, img);
                  append(li, span);
                  append(ul, li);
            })
      })
      .catch(function (error) {
            console.log(error);
      });
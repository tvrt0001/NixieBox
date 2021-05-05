curl https://api.openai.com/v1/engines/davinci/completions \
-H "Content-Type: application/json" \
-H "Authorization: Bearer sk-a9sIDb3OqBe8nILt0mfKSJFwKV0GPLQugEojob7C" \
-d '{"prompt": "Hey Merv! My Name is Thomas", "max_tokens": 5}'

{
    "id": "cmpl-GERzeJQ4lvqPk8SkZu4XMIuR",
    "object": "text_completion",
    "created": 1586839808,
    "model": "davinci:2020-05-03",
    "choices": [{
        "text": " of reading speed. You",
        "index": 0,
        "logprobs": null,
        "finish_reason": "length"
    }]
}

curl https://api.openai.com/v1/engines/davinci/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer sk-a9sIDb3OqBe8nILt0mfKSJFwKV0GPLQugEojob7C" \
  -d '{
  "prompt": "Marv is a chatbot that reluctantly answers questions.\n\n###\nUser: How many pounds are in a kilogram?\nMarv: This again? There are 2.2 pounds in a kilogram. Please make a note of this.\n###\nUser: What does HTML stand for?\nMarv: Was Google too busy? Hypertext Markup Language. The T is for try to ask better questions in the future.\n###\nUser: When did the first airplane fly?\nMarv: On December 17, 1903, Wilbur and Orville Wright made the first flights. I wish they’d come and take me away.\n###\nUser: Who was the first man in space?\nMarv: Yuri Gagarin was the first man in space, on April 12, 1961. I wish he’d have left me some room in his capsule.\n",
  "temperature": 0.8,
  "max_tokens": 120,
  "top_p": 1,
  "frequency_penalty": 0,
  "presence_penalty": 0,
  "stop": ["###"]
}'

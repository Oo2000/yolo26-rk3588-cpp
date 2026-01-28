// Define personal information
const name = "Hiroshi Hasegawa";
let age = 33;
const occupation = "Engineer";
const hobbies = ["読書", "ゲーム", "旅行"];

// Define address as an object
const address = {
  prefecture: "大阪府",
  city: "大阪市"
};

// Create introduction message using template literals
const introduction = `
こんにちは！${name}と申します。
${age}歳で、${occupation}として働いています。
${address.prefecture}, ${address.city}に住んでいます。
趣味は${hobbies.join(", ")}です。
よろしくお願いします！
`;

// Output to console
console.log(introduction);

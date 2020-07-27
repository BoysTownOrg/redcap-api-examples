function postToRedcap(body) {
  // https://developer.mozilla.org/en-US/docs/Web/API/WindowOrWorkerGlobalScope/fetch
  return fetch("https://study.boystown.org/api/", {
    method: "POST",
    headers: {
      "Content-Type": "application/x-www-form-urlencoded",
      Accept: "application/json",
    },
    body: body,
  });
}

export function uploadToRedcap(token) {
  postToRedcap("token=" + token + "&content=generateNextRecordName")
    .then(function (response) {
      return response.text();
    })
    .then(function (text) {
      const id = text;
      postToRedcap(
        "token=" +
          token +
          "&content=record&format=json&type=flat&overwriteBehavior=normal&forceAutoNumber=false&data=[" +
          JSON.stringify({ record_id: id, scent: "delightful" }) +
          "]&returnContent=count&returnFormat=json"
      );
    });
}

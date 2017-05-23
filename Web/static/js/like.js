/**
 * Created by lionzxy on 23.05.17.
 */
function setLike(id, is_like, is_question, callback) {
    $.ajax({
        url: '/api/v1/like/',
        type: 'POST',
        data: $.param({
            id: id,
            is_like: is_like,
            is_questions: is_question
        }),
        success: function (data) {
            if (data.status == 'ok') {
                console.log("OK");
                console.log(data);

                callback(data.answer.rating);
            } else {
                console.log(data)
            }
        },
        error: function () {
            console.log("error");
        }
    })
}

$(".fa-caret-up").click(function (item) {
    var question_id = $(this).parent().parent().data().id;
    setLike(question_id, 'True', 'True', function (rating) {
        $(this).parent().parent().find(".score").content = rating;
    })
});

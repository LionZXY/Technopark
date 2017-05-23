/**
 * Created by lionzxy on 23.05.17.
 */

$("#button_login").click(function () {
    $(".showbox").css("display", "block");
    $("#button_login").css("display", "none");
    var form = $("#form_answer").serialize();
    form += '&question_id=' + $("#main-question")[0].dataset.id;
    console.log(form);
    $.ajax({
        url: '/api/v1/answer/',
        type: 'POST',
        data: form,
        success: function (data) {
            if (data.status == 'ok') {
                console.log("OK");
                console.log(data);
                notifySucsess();
                //TODO update data

            } else {
                notifyAboutError(data.message, data.fields);
                console.log(data)
            }
            $(".showbox").css("display", "none");
            $("#button_login").css("display", "block");
        },
        error: function () {
            console.log("error");
            notifyAboutError("Ошибка сети");
            $(".showbox").css("display", "none");
            $("#button_login").css("display", "block");
        }
    })
});
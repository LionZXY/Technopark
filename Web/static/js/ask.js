/**
 * Created by lionzxy on 22.05.17.
 */

$("#button_login").click(function () {
    $(".showbox").css("display", "block");
    $("#button_login").css("display", "none");
    $.ajax({
        url: '/api/v1/ask/',
        type: 'POST',
        data: $("#form_ask").serialize(),
        success: function (data) {
            if (data.status == 'ok') {
                console.log("OK");
                console.log(data);

                redirect("/question/"+data.answer.id)

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
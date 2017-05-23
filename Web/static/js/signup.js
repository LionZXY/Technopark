/**
 * Created by lionzxy on 22.05.17.
 */

$("#button_login").click(function () {
    $(".showbox").css("display", "block");
    $("#button_login").css("display", "none");
    $.ajax({
        url: '/api/v1/signup/',
        type: 'POST',
        data: $("#form_signup").serialize(),
        success: function (data) {
            if (data.status == 'ok') {
                console.log("OK");
                console.log(data);
                console.log(data.headers);
                console.log(window.location.hostname);

                redirect("login")

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
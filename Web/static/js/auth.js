/**
 * Created by lionzxy on 22.05.17.
 */

function notifyAboutError(message_error) {
    content = $(".main-content");
    if (content.has(".alert"))
        content.find(".alert").remove();
    content.prepend($(' <div class="alert alert-danger"> <strong>Ошибка авторизации</strong> ' + message_error + '. </div>'));
}

$("#button_login").click(function () {
    $(".showbox").css("display", "block");
    $("#button_login").css("display", "none");
    $.ajax({
        url: '/api/v1/login/',
        type: 'POST',
        data: $("#form_login").serialize(),
        success: function (data) {
            if (data.status == 'ok') {
                console.log("OK");
                console.log(data);
                console.log(data.headers);
                console.log(window.location.hostname);

                redirect(findGetParameter("continue"))

            } else {
                notifyAboutError(data.message);
                $("field_login").addClass("has-error");
                $("field_password").addClass("has-error");
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


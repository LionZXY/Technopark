/**
 * Created by lionzxy on 22.05.17.
 */
function notifyAboutError(message_error, invalid_ids) {
    invalid_ids = typeof invalid_ids !== 'undefined' ? invalid_ids : [];
    var content = $(".main-content");
    if (content.has(".alert"))
        content.find(".alert").remove();
    content.prepend($(' <div class="alert alert-danger"> <strong>Ошибка регистрации</strong> ' + message_error + '. </div>'));
    $(".form-control").removeClass("has-error");

    invalid_ids.forEach(function (str) {
        $("#id_" + str).parent().addClass("has-error")
    })
}

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
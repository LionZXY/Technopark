/**
 * Created by lionzxy on 22.05.17.
 */
function getCookie(name) {
    var cookieValue = null;
    if (document.cookie && document.cookie !== '') {
        var cookies = document.cookie.split(';');
        for (var i = 0; i < cookies.length; i++) {
            var cookie = $.trim(cookies[i]);
            // Does this cookie string begin with the name we want?
            if (cookie.substring(0, name.length + 1) === (name + '=')) {
                cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                break;
            }
        }
    }
    return cookieValue;
}

var csrftoken = getCookie('csrftoken');

function csrfSafeMethod(method) {
    // these HTTP methods do not require CSRF protection
    return (/^(GET|HEAD|OPTIONS|TRACE)$/.test(method));
}

$.ajaxSetup({
    beforeSend: function (xhr, settings) {
        if (!csrfSafeMethod(settings.type) && !this.crossDomain) {
            xhr.setRequestHeader("X-CSRFToken", csrftoken);
        }
    }
});

function getFullHost() {
    // TODO добавить порт
    return window.location.protocol + "://" + window.location.href;
}

function redirect(url) {
    if (url == null)
        return redirect("/");
    var ua = navigator.userAgent.toLowerCase(),
        isIE = ua.indexOf('msie') !== -1,
        version = parseInt(ua.substr(4, 2), 10);

    // Internet Explorer 8 and lower
    if (isIE && version < 9) {
        var link = document.createElement('a');
        link.href = url;
        document.body.appendChild(link);
        link.click();
    }

    // All other browsers can use the standard window.location.href (they don't lose HTTP_REFERER like Internet Explorer 8 & lower does)
    else {
        window.location.href = url;
    }
    return true;
}

function findGetParameter(parameterName) {
    var result = null,
        tmp = [];
    location.search
        .substr(1)
        .split("&")
        .forEach(function (item) {
            tmp = item.split("=");
            if (tmp[0] === parameterName) result = decodeURIComponent(tmp[1]);
        });
    return result;
}

function notifyAboutError(message_error, invalid_ids) {
    invalid_ids = typeof invalid_ids !== 'undefined' ? invalid_ids : [];
    var content = $(".main-content");
    if (content.has(".alert"))
        content.find(".alert").remove();
    content.prepend($(' <div class="alert alert-danger"> <strong>Ошибка</strong> ' + message_error + '. </div>'));
    $(".form-control").removeClass("has-error");

    invalid_ids.forEach(function (str) {
        $("#id_" + str).parent().addClass("has-error")
    })
}
function notifySucsess() {
    var content = $(".main-content");
    if (content.has(".alert"))
        content.find(".alert").remove();
}